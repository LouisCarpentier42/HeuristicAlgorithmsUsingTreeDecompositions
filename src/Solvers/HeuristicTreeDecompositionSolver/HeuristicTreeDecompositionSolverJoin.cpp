//
// Created by louis on 18/11/2021.
//

#include "HeuristicTreeDecompositionSolver.h"

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::handleJoinBag(const DataStructures::JoinBag* bag) const
{
    DataStructures::ColouringQueue leftChildSolutions = solveAtBag(bag->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solveAtBag(bag->getRightChild());

    DataStructures::ColouringQueue newSolutions = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::MutableColouring{colouring};
            // TODO, if the left colouring and right colouring differ too much, skip them
            for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
            {
                if (colouring->isColoured(vertex)) continue; // Skip precoloured vertices
                if (leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    int leftNbHappyVertices{evaluator->evaluate(newColouring)};
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
                    int rightNbHappyVertices{evaluator->evaluate(newColouring)};

                    if (leftNbHappyVertices > rightNbHappyVertices) // TODO probably can be done with evaluator(left, right)
                    {
                        newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    }
                    // TODO If both are equally good, select random or add both
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