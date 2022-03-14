//
// Created by louis on 22/11/2021.
//

#include "ConcreteJoinNodeHandlers.h"

#include <algorithm>

Solvers::DynamicOrderJoinNodeHandler::DynamicOrderJoinNodeHandler(
        std::shared_ptr<const EvaluationMerger>& evaluationMerger,
        double percentMustBeEqual,
        Solvers::DynamicOrderJoinNodeHandler::Order order)
    : PairwiseCombineJoinHandler{evaluationMerger, percentMustBeEqual}
{
    switch (order)
    {
        case Order::mostColouredNeighboursFirst:
            vertexSelector = new MostColouredNeighboursSelector{};
            break;
        case Order::fewestColouredNeighboursFirst:
            vertexSelector = new FewestColouredNeighboursSelector{};
            break;
        case Order::mostPotentialHappyNeighbours:
            vertexSelector = new MostPotentialHappyNeighboursSelector{};
            break;
        case Order::mostPercentPotentialHappyNeighbours:
            vertexSelector = new MostPercentPotentialHappyNeighboursSelector{};
            break;
    }
}

void Solvers::DynamicOrderJoinNodeHandler::addMergedEntries(
        std::shared_ptr<DataStructures::JoinNode>& node,
        const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
        const std::shared_ptr<DataStructures::TableEntry>& rightEntry) const
{
    // The colour assignments used to construct a new assignment
    std::vector<std::shared_ptr<DataStructures::ColourAssignment>> oldColourAssignments{leftEntry->getColourAssignments(), rightEntry->getColourAssignments()};

    // Create a colour assignment
    std::shared_ptr<DataStructures::ColourAssignment> leftEntryAssignments = leftEntry->getColourAssignments();
    std::shared_ptr<DataStructures::ColourAssignment> rightEntryAssignments = rightEntry->getColourAssignments();
    std::shared_ptr<DataStructures::ColourAssignment> assignments = std::make_shared<DataStructures::ColourAssignment>
    (
        node,
        leftEntryAssignments,
        rightEntryAssignments
    );

    std::set<DataStructures::VertexType> remainingVerticesToColour{verticesToColour.begin(), verticesToColour.end()};
    int initialMergedEvaluation{evaluationMerger->mergeEvaluations(leftEntry->getEvaluation(), rightEntry->getEvaluation())};
    int previousEvaluation{initialMergedEvaluation};
    while (!remainingVerticesToColour.empty())
    {
        auto it = vertexSelector->select(remainingVerticesToColour, graph, assignments);
        DataStructures::VertexType vertex{*it};
        remainingVerticesToColour.erase(it);

        // If the vertices have the same colour, then you only need to re-evaluate once
        if (leftEntry->getColourAssignments()->getColour(vertex) == rightEntry->getColourAssignments()->getColour(vertex))
        {
            assignments->assignColour(vertex, leftEntry->getColourAssignments()->getColour(vertex));
            previousEvaluation = evaluator->evaluate(vertex, oldColourAssignments, assignments, graph, previousEvaluation);
        }
        else
        {
            assignments->assignColour(vertex, leftEntry->getColourAssignments()->getColour(vertex));
            int leftEvaluation{evaluator->evaluate(vertex, oldColourAssignments, assignments, graph, previousEvaluation)};
            assignments->assignColour(vertex, rightEntry->getColourAssignments()->getColour(vertex));
            int rightEvaluation{evaluator->evaluate(vertex, oldColourAssignments, assignments, graph, previousEvaluation)};

            if (leftEvaluation > rightEvaluation)
            {
                assignments->assignColour(vertex, leftEntry->getColourAssignments()->getColour(vertex));
                previousEvaluation = leftEvaluation;
            }
            else
            {
                // The colour of the vertex is already set to the colour in the right entry
                previousEvaluation = rightEvaluation;
            }
        }
    }

    std::shared_ptr<DataStructures::TableEntry> newEntry = std::make_shared<DataStructures::TableEntry>(
            previousEvaluation,
            assignments
        );
    node->getTable().push(newEntry);
}

int Solvers::DynamicOrderJoinNodeHandler::VertexSelector::getNbColouredNeighbours(
        DataStructures::VertexType vertex,
        const std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::ColourAssignment>& assignments)
{
    return std::count_if(
            graph->getNeighbours(vertex).begin(),
            graph->getNeighbours(vertex).end(),
            [assignments](auto neighbour){ return assignments->isColoured(neighbour); });
}

int Solvers::DynamicOrderJoinNodeHandler::VertexSelector::getNbPotentialHappyNeighbours(
        DataStructures::VertexType vertex,
        const std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::ColourAssignment>& assignments)
{
    int nbPotentialHappyNeighbours{0};
    for (DataStructures::VertexType potentialHappyNeighbour : graph->getNeighbours(vertex))
    {
        DataStructures::ColourType colourNeighbours{0};
        bool canBeHappy{true};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(potentialHappyNeighbour))
        {
            if (assignments->isColoured(neighbour))
            {
                if (colourNeighbours == 0)
                {
                    colourNeighbours = assignments->getColour(neighbour);
                }
                else if (assignments->getColour(neighbour) != colourNeighbours)
                {
                    canBeHappy = false;
                    break;
                }
            }
        }

        if (canBeHappy) nbPotentialHappyNeighbours++;
    }
    return nbPotentialHappyNeighbours;
}


DataStructures::BagContent::iterator Solvers::DynamicOrderJoinNodeHandler::MostColouredNeighboursSelector::select(
        DataStructures::BagContent& bagContent,
        const std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::ColourAssignment>& assignments) const
{
    auto bestIterator = bagContent.begin();
    int bestNbColouredNeighbours{0};
    for (auto it = bagContent.begin(); it != bagContent.end(); ++it)
    {
        int nbColouredNeighbours{getNbColouredNeighbours(*it, graph, assignments)};
        if (nbColouredNeighbours > bestNbColouredNeighbours)
        {
            bestIterator = it;
            bestNbColouredNeighbours = nbColouredNeighbours;
        }
    }
    return bestIterator;
}

DataStructures::BagContent::iterator Solvers::DynamicOrderJoinNodeHandler::FewestColouredNeighboursSelector::select(
        DataStructures::BagContent& bagContent,
        const std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::ColourAssignment>& assignments) const
{
    auto bestIterator = bagContent.begin();
    int bestNbColouredNeighbours{static_cast<int>(graph->getNbVertices())};
    for (auto it = bagContent.begin(); it != bagContent.end(); ++it)
    {
        int nbColouredNeighbours{getNbColouredNeighbours(*it, graph, assignments)};
        if (nbColouredNeighbours < bestNbColouredNeighbours)
        {
            bestIterator = it;
            bestNbColouredNeighbours = nbColouredNeighbours;
        }
    }
    return bestIterator;
}

DataStructures::BagContent::iterator Solvers::DynamicOrderJoinNodeHandler::MostPotentialHappyNeighboursSelector::select(
        DataStructures::BagContent& bagContent,
        const std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::ColourAssignment>& assignments) const
{
    auto bestIterator = bagContent.begin();
    int bestNbPotentialHappyNeighbours{0};
    for (auto it = bagContent.begin(); it != bagContent.end(); ++it)
    {
        int nbPotentialHappyNeighbours{getNbPotentialHappyNeighbours(*it, graph, assignments)};
        if (nbPotentialHappyNeighbours < bestNbPotentialHappyNeighbours)
        {
            bestIterator = it;
            bestNbPotentialHappyNeighbours = nbPotentialHappyNeighbours;
        }
    }
    return bestIterator;
}

DataStructures::BagContent::iterator Solvers::DynamicOrderJoinNodeHandler::MostPercentPotentialHappyNeighboursSelector::select(
        DataStructures::BagContent& bagContent,
        const std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::ColourAssignment>& assignments) const
{
    auto bestIterator = bagContent.begin();
    double bestPercentPotentialHappyNeighbours{0.0};
    for (auto it = bagContent.begin(); it != bagContent.end(); ++it)
    {
        double percentPotentialHappyNeighbours{
            (double)getNbPotentialHappyNeighbours(*it, graph, assignments) / (double)graph->getDegree(*it)
        };
        if (percentPotentialHappyNeighbours < bestPercentPotentialHappyNeighbours)
        {
            bestIterator = it;
            bestPercentPotentialHappyNeighbours = percentPotentialHappyNeighbours;
        }
    }
    return bestIterator;
}


