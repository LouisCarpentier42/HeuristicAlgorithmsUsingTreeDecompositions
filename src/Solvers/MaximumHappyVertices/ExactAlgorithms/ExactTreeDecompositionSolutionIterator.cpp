//
// Created by louis on 07/02/2022.
//

#include "ExactTreeDecompositionSolutionIterator.h"

#include <cmath>

MaximumHappyVertices::ExactTreeDecompositionSolutionIterator::ExactTreeDecompositionSolutionIterator(
        std::set<DataStructures::VertexType> verticesToConsider,
        DataStructures::Graph* graph)
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

const DataStructures::ColourAssignments MaximumHappyVertices::ExactTreeDecompositionSolutionIterator::getColourAssignments() const
{
    return colourAssignments;
}

const DataStructures::HappyVerticesAssignments MaximumHappyVertices::ExactTreeDecompositionSolutionIterator::getHappyVerticesAssignments() const
{
    return happyVerticesAssignments;
}

bool MaximumHappyVertices::ExactTreeDecompositionSolutionIterator::next()
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