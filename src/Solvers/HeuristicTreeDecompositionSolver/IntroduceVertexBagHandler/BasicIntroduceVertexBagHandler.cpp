//
// Created by louis on 21/11/2021.
//

#include "ConcreteIntroduceVertexBagHandlers.h"

DataStructures::ColouringQueue
Solvers::BasicIntroduceVertexBagHandler::handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag *bag) const
{
    DataStructures::ColouringQueue childColourings = solver->solveAtBag(bag->getChild());
    DataStructures::VertexType introducedVertex{bag->getIntroducedVertex()};

    // Precoloured vertices may not receive a new colour
    if (solver->colouring->isColoured(introducedVertex)) return childColourings;

    DataStructures::ColouringQueue newColourings = solver->createEmptyColouringQueue();
    for (DataStructures::MutableColouring* childColouring : childColourings)
    {
        for (DataStructures::ColourType colour{1}; colour <= solver->colouring->getNbColours(); colour++)
        {
            auto* newColouring = new DataStructures::MutableColouring{*childColouring};
            newColouring->setColour(introducedVertex, colour);
            std::vector<DataStructures::MutableColouring*> currentColourings;
            newColourings.push(newColouring);
        }
    }
    return newColourings;
}
