//
// Created by louis on 25/10/2021.
//

#include "GreedyMHV.h"

MaximumHappyVertices::GreedyMHV::GreedyMHV(
        const DataStructures::Graph& graph,
        const MaximumHappyVertices::PartialColouring& partialColouring) :
            MaximumHappyVerticesSolver{graph, partialColouring}
{}

MaximumHappyVertices::Colouring* MaximumHappyVertices::GreedyMHV::solve()
{
    auto* colouring = new Colouring{partialColouring};
    colourType bestColour{1};
    unsigned int bestNbHappyVertices{0};

    for (colourType colour{1}; colour <= partialColouring.getNbColours(); colour++)
    {
        colourAllVertices(colouring, colour);
        unsigned int nbHappyVertices{getNbHappyVertices(colouring)};

        if (nbHappyVertices > bestNbHappyVertices)
        {
            bestColour = colour;
            bestNbHappyVertices = nbHappyVertices;
        }
    }
    colourAllVertices(colouring, bestColour);
    return colouring;
}

void MaximumHappyVertices::GreedyMHV::colourAllVertices(MaximumHappyVertices::Colouring* colouring, colourType colour)
{
    for (vertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
    {
        if (!partialColouring.isColoured(vertex))
        {
            colouring->setColour(vertex, colour);
        }
    }
}
