//
// Created by louis on 21/11/2021.
//
#include "ConcreteJoinNodeHandlers.h"
#include "../../../rng.h"

#include <numeric>
#include <algorithm>

Solvers::StaticOrderJoinNodeHandler::StaticOrderJoinNodeHandler(
        const Solvers::EvaluationMerger* evaluationMerger,
        double percentMustBeEqual,
        Solvers::StaticOrderJoinNodeHandler::Order order)
    : PairwiseCombineJoinHandler{evaluationMerger, percentMustBeEqual}, order{order}
{ }

void Solvers::StaticOrderJoinNodeHandler::setGraph(const DataStructures::Graph* graphToSolve)
{
    NodeHandler::setGraph(graphToSolve);

    std::vector<DataStructures::VertexType> orderToColourVertices(graphToSolve->getNbVertices());
    std::iota(orderToColourVertices.begin(), orderToColourVertices.end(), 0);
    switch (order)
    {
        case Order::defaultOrder:
            break;
        case Order::greatestDegreeFirst:
            std::sort(orderToColourVertices.begin(), orderToColourVertices.end(),
                      [graphToSolve](auto v1, auto v2){ return graphToSolve->getDegree(v1) > graphToSolve->getDegree(v2); });
            break;
        case Order::smallestDegreeFirst:
            std::sort(orderToColourVertices.begin(), orderToColourVertices.end(),
                      [graphToSolve](auto v1, auto v2){ return graphToSolve->getDegree(v1) < graphToSolve->getDegree(v2); });
            break;
        case Order::random:
            std::shuffle(orderToColourVertices.begin(), orderToColourVertices.end(), RNG::rng);
            break;
    }
    // Save the vertices that are not precoloured, because those are the ones that should be coloured
    std::copy_if(
            orderToColourVertices.begin(), orderToColourVertices.end(),
        std::back_inserter(vertexOrder),
        [graphToSolve](DataStructures::VertexType vertex){return !graphToSolve->isPrecoloured(vertex);}
    );
}

void Solvers::StaticOrderJoinNodeHandler::setVerticesToColour(DataStructures::JoinNode *node)
{
    verticesToColour.clear();
    for (DataStructures::VertexType vertex : vertexOrder)
    {
        if (!graph->isPrecoloured(vertex) && std::find(node->getBagContent().begin(), node->getBagContent().end(), vertex) != node->getBagContent().end())
            verticesToColour.push_back(vertex);
    }
}

void Solvers::StaticOrderJoinNodeHandler::addMergedEntries(
        DataStructures::JoinNode* node,
       const DataStructures::TableEntry* leftEntry,
       const DataStructures::TableEntry* rightEntry) const
{
    // The colour assignments used to construct a new assignment
    std::vector<DataStructures::ColourAssignments> oldColourAssignments{leftEntry->getColourAssignments(), rightEntry->getColourAssignments()};

    // Create a colour assignment
    DataStructures::ColourAssignments assignments
    {
        leftEntry->getColourAssignments(),
        rightEntry->getColourAssignments()
    };
    for (DataStructures::VertexType vertex : node->getBagContent())
    {
        if (!graph->isPrecoloured(vertex))
            assignments.removeColour(vertex);
    }

    // Colour the vertices in the predefined order
    int initialMergedEvaluation{};
    int previousEvaluation{initialMergedEvaluation};
    for (DataStructures::VertexType vertex : verticesToColour)
    {
        // You only need to check the colour of vertices that are in the bag, thus those that are coloured in both entries
        if (leftEntry->getColourAssignments().isColoured(vertex) && rightEntry->getColourAssignments().isColoured(vertex))
        {
            // If the vertices have the same colour, then you only need to re-evaluate once
            if (leftEntry->getColourAssignments().getColour(vertex) == rightEntry->getColourAssignments().getColour(vertex))
            {
                assignments.assignColour(vertex, leftEntry->getColourAssignments().getColour(vertex));
                previousEvaluation = evaluator->evaluate(vertex, oldColourAssignments, assignments, graph, previousEvaluation);
            }
            else
            {
                assignments.assignColour(vertex, leftEntry->getColourAssignments().getColour(vertex));
                int leftEvaluation{evaluator->evaluate(vertex, oldColourAssignments, assignments, graph, previousEvaluation)};
                assignments.assignColour(vertex, rightEntry->getColourAssignments().getColour(vertex));
                int rightEvaluation{evaluator->evaluate(vertex, oldColourAssignments, assignments, graph, previousEvaluation)};

                if (leftEvaluation > rightEvaluation)
                {
                    assignments.assignColour(vertex, leftEntry->getColourAssignments().getColour(vertex));
                    previousEvaluation = leftEvaluation;
                }
                else
                {
                    // The colour of the vertex is already set to the colour in the right entry
                    previousEvaluation = rightEvaluation;
                }
            }
        }
    }

    // Add a new entry to the table
    node->getTable()->push(
        new DataStructures::TableEntry{
            previousEvaluation,
            assignments
        }
    );
}

