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
            vertexSelector = std::make_unique<MostColouredNeighboursSelector>();
            break;
        case Order::fewestColouredNeighboursFirst:
            vertexSelector = std::make_unique<FewestColouredNeighboursSelector>();
            break;
        case Order::mostSameColouredNeighboursFirst:
            vertexSelector = std::make_unique<MostSameColouredNeighboursFirst>();
            break;
        case Order::mostPercentSameColouredNeighboursFirst:
            vertexSelector = std::make_unique<MostPercentSameColouredNeighboursFirst>();
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

    for (DataStructures::VertexType vertex : verticesToColour)
        assignments->removeColour(vertex);

    vertexSelector->initializeScores(verticesToColour, assignments, graph);
    int initialMergedEvaluation{evaluationMerger->mergeEvaluations(leftEntry->getEvaluation(), rightEntry->getEvaluation())};
    int previousEvaluation{initialMergedEvaluation};
    while (vertexSelector->hasScoresLeft())
    {
        DataStructures::VertexType vertex = vertexSelector->popBest();

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

        vertexSelector->updateScores(vertex, assignments, graph);
    }

    std::shared_ptr<DataStructures::TableEntry> newEntry = std::make_shared<DataStructures::TableEntry>(
            previousEvaluation,
            assignments
        );
    node->getTable().push(newEntry);
}

int Solvers::DynamicOrderJoinNodeHandler::VertexSelector::getNbColouredNeighbours(
        DataStructures::VertexType vertex,
        std::shared_ptr<DataStructures::ColourAssignment>& assignments,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    return std::count_if(
            graph->getNeighbours(vertex).begin(),
            graph->getNeighbours(vertex).end(),
            [assignments](auto neighbour){ return assignments->isColoured(neighbour); });
}

DataStructures::VertexType Solvers::DynamicOrderJoinNodeHandler::VertexSelector::popBest()
{
    auto bestIt = scores.begin();

    for (auto it = scores.begin(); it != scores.end(); it++)
    {
        if (it->second > bestIt->second)
            bestIt = it;
    }

    scores.erase(bestIt);
    return bestIt->first;
}

bool Solvers::DynamicOrderJoinNodeHandler::VertexSelector::hasScoresLeft()
{
    return !scores.empty();
}

void Solvers::DynamicOrderJoinNodeHandler::MostColouredNeighboursSelector::initializeScores(
        const std::set<DataStructures::VertexType>& verticesToColour,
        std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    scores.clear();
    for (DataStructures::VertexType vertex : verticesToColour)
        // At the end since vertices to colour is set
        scores.emplace_hint(scores.end(), vertex, getNbColouredNeighbours(vertex, colourAssignment, graph));
}

void Solvers::DynamicOrderJoinNodeHandler::MostColouredNeighboursSelector::updateScores(
        DataStructures::VertexType colouredVertex,
        std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    for (DataStructures::VertexType neighbour : graph->getNeighbours(colouredVertex))
    {
        auto it = scores.find(neighbour);
        if (it != scores.end() )
        {
            it->second++;
        }
    }
}

void Solvers::DynamicOrderJoinNodeHandler::FewestColouredNeighboursSelector::initializeScores(
        const std::set<DataStructures::VertexType>& verticesToColour,
        std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    scores.clear();
    for (DataStructures::VertexType vertex : verticesToColour)
        // At the end since vertices to colour is set
        // Negative of nb coloured neighbours to promote vertices without coloured neighbours
        scores.emplace_hint(scores.end(), vertex, -getNbColouredNeighbours(vertex, colourAssignment, graph));
}

void Solvers::DynamicOrderJoinNodeHandler::FewestColouredNeighboursSelector::updateScores(
        DataStructures::VertexType colouredVertex,
        std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    for (DataStructures::VertexType neighbour : graph->getNeighbours(colouredVertex))
    {
        auto it = scores.find(neighbour);
        if (it != scores.end())
        {
            it->second--;
        }
    }
}

void Solvers::DynamicOrderJoinNodeHandler::MostSameColouredNeighboursFirst::initializeScores(
        const std::set<DataStructures::VertexType>& verticesToColour,
        std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    scores.clear();
    cachedColourNeighbours.clear();

    for (DataStructures::VertexType vertex : verticesToColour)
    {
        DataStructures::ColourType colourOfNeighbours{0};
        int nbNeighboursInColour{0};
        bool hasNeighboursInMultipleColours{false};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (colourAssignment->isColoured(neighbour))
            {
                if (colourOfNeighbours == 0)
                {
                    colourOfNeighbours = colourAssignment->getColour(neighbour);
                    nbNeighboursInColour++;
                }
                else if (colourOfNeighbours == colourAssignment->getColour(neighbour))
                {
                    nbNeighboursInColour++;
                }
                else // Neighbour has a different colour
                {
                    hasNeighboursInMultipleColours = true;
                    break;
                }
            }
        }

        if (hasNeighboursInMultipleColours)
        {
            scores.emplace_hint(scores.end(), vertex, 0);
        }
        else
        {
            scores.emplace_hint(scores.end(), vertex, nbNeighboursInColour);
            cachedColourNeighbours.emplace_hint(cachedColourNeighbours.end(), vertex, colourOfNeighbours);
        }

    }
}

void Solvers::DynamicOrderJoinNodeHandler::MostSameColouredNeighboursFirst::updateScores(
        DataStructures::VertexType colouredVertex,
        std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    cachedColourNeighbours.erase(colouredVertex); // It is coloured thus this vertex must not be cached anymore
    for (DataStructures::VertexType neighbour : graph->getNeighbours(colouredVertex))
    {
        auto itScores = scores.find(neighbour);
        auto itCachedColour = cachedColourNeighbours.find(neighbour);
        if (itScores != scores.end() && itCachedColour != cachedColourNeighbours.end())
        {
            if (itCachedColour->second == colourAssignment->getColour(colouredVertex))
            {
                itScores->second++;
            }
            else
            {
                itScores->second = 0;
                cachedColourNeighbours.erase(itCachedColour); // Has multiple neighbouring colours
            }
        }
    }
}

void Solvers::DynamicOrderJoinNodeHandler::MostPercentSameColouredNeighboursFirst::initializeScores(
        const std::set<DataStructures::VertexType>& verticesToColour,
        std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    scores.clear();
    cachedColourNeighbours.clear();

    for (DataStructures::VertexType vertex : verticesToColour)
    {
        DataStructures::ColourType colourOfNeighbours{0};
        double nbNeighboursInColour{0.0};
        double totalNbNeighbours{0.0};
        bool hasNeighboursInMultipleColours{false};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            totalNbNeighbours++;
            if (colourAssignment->isColoured(neighbour))
            {
                if (colourOfNeighbours == 0)
                {
                    colourOfNeighbours = colourAssignment->getColour(neighbour);
                    nbNeighboursInColour++;
                }
                else if (colourOfNeighbours == colourAssignment->getColour(neighbour))
                {
                    nbNeighboursInColour++;
                }
                else // Neighbour has a different colour
                {
                    hasNeighboursInMultipleColours = true;
                    break;
                }
            }
        }

        if (hasNeighboursInMultipleColours)
        {
            scores.emplace_hint(scores.end(), vertex, 0);
        }
        else
        {
            scores.emplace_hint(scores.end(), vertex, nbNeighboursInColour / totalNbNeighbours);
            cachedColourNeighbours.emplace_hint(cachedColourNeighbours.end(), vertex, colourOfNeighbours);
        }

    }
}

void Solvers::DynamicOrderJoinNodeHandler::MostPercentSameColouredNeighboursFirst::updateScores(
        DataStructures::VertexType colouredVertex,
        std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    cachedColourNeighbours.erase(colouredVertex); // It is coloured thus this vertex must not be cached anymore
    for (DataStructures::VertexType neighbour : graph->getNeighbours(colouredVertex))
    {
        auto itScores = scores.find(neighbour);
        auto itCachedColour = cachedColourNeighbours.find(neighbour);
        if (itScores != scores.end() && itCachedColour != cachedColourNeighbours.end())
        {
            if (itCachedColour->second == colourAssignment->getColour(colouredVertex))
            {
                itScores->second += (1.0 / (double)graph->getNeighbours(neighbour).size());
            }
            else
            {
                itScores->second = 0;
                cachedColourNeighbours.erase(itCachedColour); // Has multiple neighbouring colours
            }
        }
    }
}
