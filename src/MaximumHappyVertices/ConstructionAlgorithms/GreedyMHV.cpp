//
// Created by louis on 25/10/2021.
//

#include "GreedyMHV.h"

MaximumHappyVertices::GreedyMHV::GreedyMHV(
        const DataStructures::Graph& graph,
        const DataStructures::PartialColouring& partialColouring)
        : MaximumHappyVerticesSolver{graph, partialColouring}
{}

DataStructures::Colouring* MaximumHappyVertices::GreedyMHV::solve() const
{
    auto* colouring = new DataStructures::Colouring{partialColouring};
    DataStructures::ColourType bestColour{1};
    unsigned int bestNbHappyVertices{0};

    for (DataStructures::ColourType colour{1}; colour <= partialColouring.getNbColours(); colour++)
    {
        colourAllVertices(colouring, colour);
        unsigned int nbHappyVertices{graph.getNbHappyVertices(colouring)};

        if (nbHappyVertices > bestNbHappyVertices)
        {
            bestColour = colour;
            bestNbHappyVertices = nbHappyVertices;
        }
    }
    colourAllVertices(colouring, bestColour);
    std::cout << "[GREEDY-MHV] Nb happy vertices: " << bestNbHappyVertices << "\n"; // TODO remove
    return colouring;
}

void MaximumHappyVertices::GreedyMHV::colourAllVertices(DataStructures::Colouring* colouring, DataStructures::ColourType colour) const
{
    for (DataStructures::VertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
    {
        if (!partialColouring.isColoured(vertex))
        {
            colouring->setColour(vertex, colour);
        }
    }
}
