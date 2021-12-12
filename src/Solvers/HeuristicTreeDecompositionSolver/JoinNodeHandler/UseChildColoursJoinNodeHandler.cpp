//
// Created by louis on 12/12/2021.
//

#include "ConcreteJoinNodeHandlers.h"


DataStructures::ColouringQueue Solvers::UseChildColoursJoinNodeHandler::handleJoinNode(const DataStructures::JoinNode *node) const
{
    DataStructures::ColouringQueue leftChildSolutions = solver->solveAtNode(node->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solver->solveAtNode(node->getRightChild());

    DataStructures::ColouringQueue newSolutions = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* leftColouringExtended = new DataStructures::MutableColouring{leftColouring};
            auto* rightColouringExtended = new DataStructures::MutableColouring{rightColouring};

            for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
            {
                if (!leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                {
                    leftColouringExtended->setColour(vertex, rightColouring->getColour(vertex));
                }
                else if (leftColouring->isColoured(vertex) && !rightColouring->isColoured(vertex))
                {
                    rightColouringExtended->setColour(vertex, leftColouring->getColour(vertex));
                }
            }
            newSolutions.push(leftColouringExtended);
            newSolutions.push(rightColouringExtended);
        }
    }
    return newSolutions;
}

