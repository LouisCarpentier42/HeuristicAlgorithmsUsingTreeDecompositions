//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "ExactTreeDecompositionMHVSolutionIterator.h"

#include <cmath>

MaximumHappyVertices::ExactTreeDecompositionMHVSolutionIterator::ExactTreeDecompositionMHVSolutionIterator(
        std::set<DataStructures::VertexType>& verticesToConsider,
        const std::shared_ptr<DataStructures::Graph>& graph)
    : nbColours{static_cast<int>(graph->getNbColours())},
      verticesToConsider{std::move(verticesToConsider)},
      verticesToColour{},
      colourAssignments{graph},
      happyVerticesAssignments{graph}
{
    for (DataStructures::VertexType vertex : this->verticesToConsider)
    {
        if (graph->isPrecoloured(vertex))
        {
            colourAssignments.assignColour(vertex, graph->getColour(vertex));
        }
        else
        {
            verticesToColour.insert(vertex);
            colourAssignments.assignColour(vertex, 1);
        }
    }
}

const DataStructures::ColourAssignment MaximumHappyVertices::ExactTreeDecompositionMHVSolutionIterator::getColourAssignments() const
{
    return colourAssignments;
}

const DataStructures::HappyVerticesAssignments MaximumHappyVertices::ExactTreeDecompositionMHVSolutionIterator::getHappyVerticesAssignments() const
{
    return happyVerticesAssignments;
}

bool MaximumHappyVertices::ExactTreeDecompositionMHVSolutionIterator::next()
{
    currentHappinessAssignmentId++;

    // If all happiness assignments have been considered, move to the next colouring
    if (currentHappinessAssignmentId >= std::pow(2, verticesToConsider.size()))
    {
        currentHappinessAssignmentId = 0;

        currentColourAssignmentId++;
        if (currentColourAssignmentId >= std::pow(nbColours, verticesToColour.size()))
            return false;

        int numberToConvert{currentColourAssignmentId};
        for (DataStructures::VertexType vertex : verticesToColour)
        {
            colourAssignments.assignColour(vertex, (numberToConvert % nbColours) + 1);
            numberToConvert /= nbColours;
        }
    }

    int numberToConvert{currentHappinessAssignmentId};
    for (DataStructures::VertexType vertex : verticesToConsider)
    {
        if ((numberToConvert % 2) == 1)
            happyVerticesAssignments.makeHappy(vertex);
        else
            happyVerticesAssignments.makeUnhappy(vertex);
        numberToConvert /= 2;
    }

    return true;
}