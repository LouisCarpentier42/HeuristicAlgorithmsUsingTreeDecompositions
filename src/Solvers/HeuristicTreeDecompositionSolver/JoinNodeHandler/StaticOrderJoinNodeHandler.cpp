//
// Created by louis on 21/11/2021.
//
#include "ConcreteJoinNodeHandlers.h"

#include <numeric>
#include <algorithm>
#include <random>

Solvers::StaticOrderJoinNodeHandler::StaticOrderJoinNodeHandler(Solvers::StaticOrderJoinNodeHandler::Order order)
    : order{order}
{ }

void Solvers::StaticOrderJoinNodeHandler::setGraph(const DataStructures::Graph* graphToSolve)
{
    NodeHandler::setGraph(graphToSolve);

    static std::mt19937 rng{std::random_device{}()};
    vertexOrder = std::vector<DataStructures::VertexType>(graphToSolve->getNbVertices());
    std::iota(vertexOrder.begin(), vertexOrder.end(), 0);
    switch (order)
    {
        case Order::defaultOrder:
            break;
        case Order::greatestDegreeFirst:
            std::sort(vertexOrder.begin(), vertexOrder.end(),
                      [graphToSolve](auto v1, auto v2){ return graphToSolve->getDegree(v1) > graphToSolve->getDegree(v2); });
            break;
        case Order::smallestDegreeFirst:
            std::sort(vertexOrder.begin(), vertexOrder.end(),
                      [graphToSolve](auto v1, auto v2){ return graphToSolve->getDegree(v1) < graphToSolve->getDegree(v2); });
            break;
        case Order::random:
            std::shuffle(vertexOrder.begin(), vertexOrder.end(), rng);
            break;
    }
}

DataStructures::ColouringQueue Solvers::StaticOrderJoinNodeHandler::handleJoinNode(const DataStructures::JoinNode *node) const
{
    DataStructures::ColouringQueue leftChildSolutions = solver->solveAtNode(node->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solver->solveAtNode(node->getRightChild());

    DataStructures::ColouringQueue newSolutions = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::MutableColouring{colouring};
            for (DataStructures::VertexType vertex : vertexOrder)
            {
                if (colouring->isColoured(vertex)) continue; // Skip precoloured vertices
                if (leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    int leftNbHappyVertices{evaluator->evaluate(graph, newColouring)};
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
                    int rightNbHappyVertices{evaluator->evaluate(graph, newColouring)};

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
