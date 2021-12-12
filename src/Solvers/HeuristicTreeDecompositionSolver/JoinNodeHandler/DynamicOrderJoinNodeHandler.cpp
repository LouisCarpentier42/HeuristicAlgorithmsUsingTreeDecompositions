//
// Created by louis on 22/11/2021.
//

#include "ConcreteJoinNodeHandlers.h"

#include <algorithm>

// TODO optimize: cache the eval of vertices in bag + update in stead of recomputing each time

Solvers::DynamicOrderJoinNodeHandler::DynamicOrderJoinNodeHandler(Solvers::DynamicOrderJoinNodeHandler::Order order)
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

DataStructures::ColouringQueue Solvers::DynamicOrderJoinNodeHandler::handleJoinNode(const DataStructures::JoinNode *node) const
{
    DataStructures::ColouringQueue leftChildSolutions = solver->solveAtNode(node->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solver->solveAtNode(node->getRightChild());

    DataStructures::ColouringQueue newSolutions = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::MutableColouring{colouring};

            for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
            {
                if (colouring->isColoured(vertex))
                    continue;
                else if (leftColouring->isColoured(vertex) && !rightColouring->isColoured(vertex))
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                else if (!leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
            }

            DataStructures::BagContent verticesToColour(node->getBagSize());
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                if (!colouring->isColoured(vertex))
                    verticesToColour.push_back(vertex);
            }
            while (!verticesToColour.empty())
            {
                auto it = vertexSelector->select(verticesToColour, graph, newColouring);
                DataStructures::VertexType vertex{*it};
                verticesToColour.erase(it);

                // TODO here can be done something smarter maybe?
                newColouring->setColour(vertex, leftColouring->getColour(vertex));
                int leftNbHappyVertices{evaluator->evaluate(graph, newColouring)};
                newColouring->setColour(vertex, rightColouring->getColour(vertex));
                int rightNbHappyVertices{evaluator->evaluate(graph, newColouring)};

                if (leftNbHappyVertices > rightNbHappyVertices)
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                }
            }
            newSolutions.push(newColouring);
        }
    }
    return newSolutions;
}

int Solvers::DynamicOrderJoinNodeHandler::VertexSelector::getNbColouredNeighbours(
        DataStructures::VertexType vertex,
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring)
{
    const std::vector<DataStructures::VertexType>* neighbours{graph->getNeighbours(vertex)};
    return std::count_if(
            neighbours->begin(),
            neighbours->end(),
            [colouring](auto neighbour){ return colouring->isColoured(neighbour); });
}

int Solvers::DynamicOrderJoinNodeHandler::VertexSelector::getNbPotentialHappyNeighbours(
        DataStructures::VertexType vertex,
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring)
{
    int nbPotentialHappyNeighbours{0};
    for (DataStructures::VertexType potentialHappyNeighbour : *graph->getNeighbours(vertex))
    {
        DataStructures::ColourType colourNeighbours{0};
        bool canBeHappy{true};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(potentialHappyNeighbour))
        {
            if (colouring->isColoured(neighbour))
            {
                if (colourNeighbours == 0)
                {
                    colourNeighbours = colouring->getColour(neighbour);
                }
                else if (colouring->getColour(neighbour) != colourNeighbours)
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
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring) const
{
    auto bestIterator = bagContent.begin();
    int bestNbColouredNeighbours{getNbColouredNeighbours(*bestIterator, graph, colouring)};
    for (auto it = bagContent.begin()+1; it != bagContent.end(); ++it)
    {
        int nbColouredNeighbours{getNbColouredNeighbours(*it, graph, colouring)};
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
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring) const
{
    auto bestIterator = bagContent.begin();
    int bestNbColouredNeighbours{getNbColouredNeighbours(*bestIterator, graph, colouring)};
    for (auto it = bagContent.begin()+1; it != bagContent.end(); ++it)
    {
        int nbColouredNeighbours{getNbColouredNeighbours(*it, graph, colouring)};
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
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring) const
{
    auto bestIterator = bagContent.begin();
    int bestNbPotentialHappyNeighbours{getNbPotentialHappyNeighbours(*bestIterator, graph, colouring)};
    for (auto it = bagContent.begin()+1; it != bagContent.end(); ++it)
    {
        int nbPotentialHappyNeighbours{getNbPotentialHappyNeighbours(*it, graph, colouring)};
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
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring) const
{
    auto bestIterator = bagContent.begin();
    double bestPercentPotentialHappyNeighbours{
        (double)getNbPotentialHappyNeighbours(*bestIterator, graph, colouring) / (double)graph->getDegree(*bestIterator)
    };
    for (auto it = bagContent.begin()+1; it != bagContent.end(); ++it)
    {
        double percentPotentialHappyNeighbours{
            (double)getNbPotentialHappyNeighbours(*it, graph, colouring) / (double)graph->getDegree(*it)
        };
        if (percentPotentialHappyNeighbours < bestPercentPotentialHappyNeighbours)
        {
            bestIterator = it;
            bestPercentPotentialHappyNeighbours = percentPotentialHappyNeighbours;
        }
    }
    return bestIterator;
}


