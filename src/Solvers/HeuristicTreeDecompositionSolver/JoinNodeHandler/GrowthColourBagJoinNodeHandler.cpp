//
// Created by louis on 12/12/2021.
//

#include "ConcreteJoinNodeHandlers.h"

DataStructures::ColouringQueue Solvers::GrowthColourBagJoinNodeHandler::handleJoinNode(const DataStructures::JoinNode *node) const
{
    DataStructures::ColouringQueue leftChildSolutions = solver->solveAtNode(node->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solver->solveAtNode(node->getRightChild());

    DataStructures::ColouringQueue newSolutions = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::MutableColouring{colouring};

            
        }
    }
    return newSolutions;
}

