//
// Created by louis on 18/11/2021.
//

#include "HeuristicTreeDecompositionSolver.h"

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag* bag) const
{
    DataStructures::ColouringQueue childColourings = solveAtBag(bag->getChild());
    DataStructures::VertexType introducedVertex{bag->getIntroducedVertex()};

    // Precoloured vertices may not receive a new colour
    if (colouring->isColoured(introducedVertex)) return childColourings;

    DataStructures::ColouringQueue newColourings = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* childColouring : childColourings)
    {
        for (DataStructures::ColourType colour{1}; colour <= colouring->getNbColours(); colour++)
        {
            auto* newColouring = new DataStructures::MutableColouring{*childColouring};
            newColouring->setColour(introducedVertex, colour);
            std::vector<DataStructures::MutableColouring*> currentColourings;
            newColourings.push(newColouring);
        }
    }
    return newColourings;
}