//
// Created by louis on 30/11/2021.
//

#include "ConcreteIntroduceVertexBagHandlers.h"

DataStructures::ColouringQueue Solvers::BestColourIntroduceVertexBagHandler::handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag *bag) const
{
    DataStructures::ColouringQueue childColourings = solver->solveAtBag(bag->getChild());
    DataStructures::VertexType introducedVertex{bag->getIntroducedVertex()};

    // Precoloured vertices may not receive a new colour
    if (solver->colouring->isColoured(introducedVertex)) return childColourings;

    DataStructures::ColouringQueue bestColourings = solver->createEmptyColouringQueue();
    DataStructures::ColouringQueue allColourings = solver->createEmptyColouringQueue();
    for (DataStructures::MutableColouring* childColouring : childColourings)
    {
        DataStructures::ColouringQueue newColourings = solver->createEmptyColouringQueue();
        for (DataStructures::ColourType colour{1}; colour <= solver->colouring->getNbColours(); colour++)
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
