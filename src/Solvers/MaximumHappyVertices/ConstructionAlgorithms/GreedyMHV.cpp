//
// Created by louis on 25/10/2021.
//

#include "GreedyMHV.h"

DataStructures::MutableColouring* MaximumHappyVertices::GreedyMHV::solve(
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring) const
{
    auto* colouringToColour = new DataStructures::MutableColouring{colouring};
    colourAllVertices(graph, colouring, colouringToColour, 1);
    DataStructures::ColourType bestColour{1};
    int bestNbHappyVertices{evaluator->evaluate(graph, colouringToColour)};

    for (DataStructures::ColourType colour{2}; colour <= colouring->getNbColours(); colour++)
    {
        colourAllVertices(graph, colouring, colouringToColour, colour);
        int nbHappyVertices{evaluator->evaluate(graph, colouringToColour)};
        if (nbHappyVertices > bestNbHappyVertices)
        {
            bestColour = colour;
            bestNbHappyVertices = nbHappyVertices;
        }
    }
    colourAllVertices(graph, colouring, colouringToColour, bestColour);
    return colouringToColour;
}

void MaximumHappyVertices::GreedyMHV::colourAllVertices(
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* initialColouring,
        DataStructures::MutableColouring* colouringToColour,
        DataStructures::ColourType colour)
{
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!initialColouring->isColoured(vertex))
        {
            colouringToColour->setColour(vertex, colour);
        }
    }
}
