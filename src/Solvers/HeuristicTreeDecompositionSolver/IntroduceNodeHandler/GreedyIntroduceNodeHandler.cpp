//
// Created by louis on 21/11/2021.
//

#include "ConcreteIntroduceNodeHandlers.h"

DataStructures::ColouringQueue Solvers::GreedyIntroduceNodeHandler::handleIntroduceNode(const DataStructures::IntroduceNode *node) const
{
    DataStructures::ColouringQueue childColourings = solver->solveAtNode(node->getChild());
    DataStructures::VertexType introducedVertex{node->getIntroducedVertex()};

    // Precoloured vertices may not receive a new colour
    if (colouring->isColoured(introducedVertex)) return childColourings;

    DataStructures::ColouringQueue newColourings = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* childColouring : childColourings)
    {
        for (DataStructures::ColourType colour{1}; colour <= colouring->getNbColours(); colour++)
        {
            auto* newColouring = new DataStructures::MutableColouring{*childColouring};
            newColouring->setColour(introducedVertex, colour);
            newColourings.push(newColouring);
        }
    }
    return newColourings;
}
