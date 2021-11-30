//
// Created by louis on 21/11/2021.
//
#include "ConcreteJoinBagHandlers.h"

#include <numeric>
#include <algorithm>
#include <random>

Solvers::StaticOrderJoinBagHandler::StaticOrderJoinBagHandler(DataStructures::Graph* graph, Solvers::StaticOrderJoinBagHandler::Order order)
: vertexOrder{std::vector<DataStructures::VertexType>(graph->getNbVertices())}
{
    static std::mt19937 rng{std::random_device{}()};
    std::iota(vertexOrder.begin(), vertexOrder.end(), 0);
    switch (order)
    {
        case Order::defaultOrder:
            break;
        case Order::greatestDegreeFirst:
            std::sort(vertexOrder.begin(), vertexOrder.end(),
                      [graph](auto v1, auto v2){ return graph->getDegree(v1) > graph->getDegree(v2); });
            break;
        case Order::smallestDegreeFirst:
            std::sort(vertexOrder.begin(), vertexOrder.end(),
                      [graph](auto v1, auto v2){ return graph->getDegree(v1) < graph->getDegree(v2); });
            break;
        case Order::random:
            std::shuffle(vertexOrder.begin(), vertexOrder.end(), rng);
            break;
    }
}

DataStructures::ColouringQueue Solvers::StaticOrderJoinBagHandler::handleJoinBag(const DataStructures::JoinBag *bag) const
{
    DataStructures::ColouringQueue leftChildSolutions = solver->solveAtBag(bag->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solver->solveAtBag(bag->getRightChild());

    DataStructures::ColouringQueue newSolutions = solver->createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::MutableColouring{solver->colouring};
            for (DataStructures::VertexType vertex : vertexOrder)
            {
                if (solver->colouring->isColoured(vertex)) continue; // Skip precoloured vertices
                if (leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    int leftNbHappyVertices{solver->evaluator->evaluate(newColouring)};
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
                    int rightNbHappyVertices{solver->evaluator->evaluate(newColouring)};

                    if (leftNbHappyVertices > rightNbHappyVertices)
                    {
                        newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    }
                }
                else if (leftColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                }
                else if (rightColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
                }
            }
            newSolutions.push(newColouring);
        }
    }
    return newSolutions;
}
