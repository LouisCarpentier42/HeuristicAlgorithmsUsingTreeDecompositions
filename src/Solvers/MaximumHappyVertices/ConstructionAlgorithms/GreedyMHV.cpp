//
// Created by louis on 25/10/2021.
//

#include "GreedyMHV.h"

#include <numeric>
#include <algorithm>
#include <queue>

MaximumHappyVertices::GreedyMHV::GreedyMHV(
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring)
    : MaximumHappyVerticesSolver(graph, colouring)
{}


DataStructures::MutableColouring* MaximumHappyVertices::GreedyMHV::solve() const
{
    auto* colouringToColour = new DataStructures::MutableColouring{colouring};
    colourAllVertices(colouringToColour, 1);
    DataStructures::ColourType bestColour{1};
    int bestNbHappyVertices{evaluator->evaluate(colouringToColour)};

    for (DataStructures::ColourType colour{2}; colour <= colouring->getNbColours(); colour++)
    {
        colourAllVertices(colouringToColour, colour);
        int nbHappyVertices{evaluator->evaluate(colouringToColour)};
        if (nbHappyVertices > bestNbHappyVertices)
        {
            bestColour = colour;
            bestNbHappyVertices = nbHappyVertices;
        }
    }
    colourAllVertices(colouringToColour, bestColour);
    return colouringToColour;
}

void MaximumHappyVertices::GreedyMHV::colourAllVertices(DataStructures::MutableColouring* colouringToColour, DataStructures::ColourType colour) const
{
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!colouring->isColoured(vertex))
        {
            colouringToColour->setColour(vertex, colour);
        }
    }
}
