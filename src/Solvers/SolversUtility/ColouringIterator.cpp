//
// Created by louis on 13/02/2022.
//

#include "ColouringIterator.h"

#include <cmath>

Solvers::ColouringIterator::ColouringIterator(
        std::set<DataStructures::VertexType> verticesToConsider,
        DataStructures::Graph* graph)
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

const DataStructures::ColourAssignments Solvers::ColouringIterator::getValue() const
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