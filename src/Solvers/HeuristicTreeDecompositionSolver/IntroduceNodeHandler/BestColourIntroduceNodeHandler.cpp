//
// Created by louis on 30/11/2021.
//

#include "ConcreteIntroduceNodeHandlers.h"

DataStructures::ColouringQueue Solvers::BestColourIntroduceNodeHandler::handleIntroduceNode(const DataStructures::IntroduceNode *node) const
{
    DataStructures::ColouringQueue childColourings = solver->solveAtNode(node->getChild());
    DataStructures::VertexType introducedVertex{node->getIntroducedVertex()};

    // Precoloured vertices may not receive a new colour
    if (colouring->isColoured(introducedVertex)) return childColourings;

    DataStructures::ColouringQueue bestColourings = createEmptyColouringQueue();
    DataStructures::ColouringQueue allColourings = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* childColouring : childColourings)
    {
        DataStructures::ColouringQueue newColourings = createEmptyColouringQueue();
        for (DataStructures::ColourType colour{1}; colour <= colouring->getNbColours(); colour++)
        {
            auto* newColouring = new DataStructures::MutableColouring{*childColouring};
            newColouring->setColour(introducedVertex, colour);
            newColourings.push(newColouring);
            allColourings.push(newColouring);
        }
        bestColourings.push(newColourings.popBestColouring());
    }

    // Fill the best colourings queue with extra colourings
    while (!bestColourings.reachedCapacity() && !allColourings.isEmpty())
        bestColourings.push(allColourings.popBestColouring());

    return bestColourings;
}
