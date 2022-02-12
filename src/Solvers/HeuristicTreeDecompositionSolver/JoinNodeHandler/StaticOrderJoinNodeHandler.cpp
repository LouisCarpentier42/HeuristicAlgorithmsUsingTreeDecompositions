//
// Created by louis on 21/11/2021.
//
#include "ConcreteJoinNodeHandlers.h"
#include "../../../rng.h"

#include <numeric>
#include <algorithm>

Solvers::StaticOrderJoinNodeHandler::StaticOrderJoinNodeHandler(
        const Solvers::EvaluationMerger* evaluationMerger,
        Solvers::StaticOrderJoinNodeHandler::Order order)
    : JoinNodeHandler{evaluationMerger}, order{order}
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


void Solvers::StaticOrderJoinNodeHandler::handleJoinNode(DataStructures::JoinNode* node) const
{
    solver->solveAtNode(node->getLeftChild());
    solver->solveAtNode(node->getRightChild());

    for (DataStructures::TableEntry* leftEntry : *node->getLeftChild()->getTable())
    {
        for (DataStructures::TableEntry* rightEntry : *node->getRightChild()->getTable())
        {
            // Create a colour assignment
            DataStructures::ColourAssignments assignments
            {
                leftEntry->getColourAssignments(),
                rightEntry->getColourAssignments()
            };
            // Colour the vertices in the predefined order
            int initialMergedEvaluation{evaluationMerger->mergeEvaluations(leftEntry->getEvaluation(), rightEntry->getEvaluation())};
            int previousEvaluation{initialMergedEvaluation};
            for (DataStructures::VertexType vertex : vertexOrder)
            {
                // If the vertex is coloured in both entries, then the best colour is used
                if (leftEntry->getColourAssignments().isColoured(vertex) && leftEntry->getColourAssignments().isColoured(vertex))
                {
                    assignments.assignColour(vertex, leftEntry->getColourAssignments().getColour(vertex));
                    int leftEvaluation{evaluator->evaluate(vertex, assignments, graph, previousEvaluation)};
                    assignments.assignColour(vertex, leftEntry->getColourAssignments().getColour(vertex));
                    int rightEvaluation{evaluator->evaluate(vertex, assignments, graph, previousEvaluation)};

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
                // If the vertex is coloured in only one entry, then that colour is copied
                else if (leftEntry->getColourAssignments().isColoured(vertex))
                {
                    assignments.assignColour(vertex, leftEntry->getColourAssignments().getColour(vertex));
                }
                else if (rightEntry->getColourAssignments().isColoured(vertex))
                {
                    assignments.assignColour(vertex, rightEntry->getColourAssignments().getColour(vertex));
                }
            }

            // Add a new entry to the table
            node->getTable()->push(
                new DataStructures::TableEntry{
                    evaluator->evaluate(node->getBagContent(), assignments, graph, initialMergedEvaluation),
                    assignments
                }
            );
        }
    }
}
