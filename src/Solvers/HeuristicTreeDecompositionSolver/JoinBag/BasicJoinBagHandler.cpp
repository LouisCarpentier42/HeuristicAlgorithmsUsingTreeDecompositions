//
// Created by louis on 21/11/2021.
//
#include "ConcreteJoinBagHandlers.h"

DataStructures::ColouringQueue Solvers::BasicJoinBagHandler::handleJoinBag(const DataStructures::JoinBag *bag) const
{
    DataStructures::ColouringQueue leftChildSolutions = solver->solveAtBag(bag->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solver->solveAtBag(bag->getRightChild());

    DataStructures::ColouringQueue newSolutions = solver->createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::MutableColouring{solver->colouring};
            for (DataStructures::VertexType vertex{0}; vertex < solver->graph->getNbVertices(); vertex++)
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
