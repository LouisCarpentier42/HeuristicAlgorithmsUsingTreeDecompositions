//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "ColouringIterator.h"

#include <cmath>

Solvers::ColouringIterator::ColouringIterator(
        std::set<DataStructures::VertexType> verticesToConsider,
        std::shared_ptr<DataStructures::Graph>& graph)
    : nbColours{static_cast<int>(graph->getNbColours())},
      verticesToConsider{std::move(verticesToConsider)},
      verticesToColour{},
      colourAssignments{graph}
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

const DataStructures::ColourAssignment Solvers::ColouringIterator::getValue() const
{
    return colourAssignments;
}

bool Solvers::ColouringIterator::next()
{
    currentColourAssignmentId++;
    if (currentColourAssignmentId >= std::pow(nbColours, verticesToColour.size()))
        return false;

    int numberToConvert{currentColourAssignmentId};
    for (DataStructures::VertexType vertex : verticesToColour)
    {
        colourAssignments.assignColour(vertex, (numberToConvert % nbColours) + 1);
        numberToConvert /= nbColours;
    }

    return true;
}