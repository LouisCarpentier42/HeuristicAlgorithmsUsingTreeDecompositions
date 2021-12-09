//
// Created by louis on 25/10/2021.
//

#include "GreedyMHV.h"

#include <numeric>
#include <algorithm>
#include <queue>

//MaximumHappyVertices::GreedyMHV::GreedyMHV( // TOOD comments
//        const DataStructures::Graph* graph,
//        const DataStructures::Colouring* colouring)
//    : MaximumHappyVerticesSolver(graph, colouring)
//{}


DataStructures::MutableColouring* MaximumHappyVertices::GreedyMHV::solve(const DataStructures::Graph* graph, const DataStructures::Colouring* colouring) const
{
    auto* colouringToColour = new DataStructures::MutableColouring{colouring};
    colourAllVertices(graph, colouring, colouringToColour, 1);
//    colourAllVertices(colouringToColour, 1);
    DataStructures::ColourType bestColour{1};
//    int bestNbHappyVertices{evaluator->evaluate(colouringToColour)};
    int bestNbHappyVertices{evaluator->evaluate(graph, colouringToColour)};

    for (DataStructures::ColourType colour{2}; colour <= colouring->getNbColours(); colour++)
    {
        colourAllVertices(graph, colouring, colouringToColour, colour);
//        colourAllVertices(colouringToColour, colour);
        int nbHappyVertices{evaluator->evaluate(graph, colouringToColour)};
//        int nbHappyVertices{evaluator->evaluate(colouringToColour)};
        if (nbHappyVertices > bestNbHappyVertices)
        {
            bestColour = colour;
            bestNbHappyVertices = nbHappyVertices;
        }
    }
//    colourAllVertices(colouringToColour, bestColour);
    colourAllVertices(graph, colouring, colouringToColour, bestColour);
    return colouringToColour;
}

// TODO set param a little cleaner
void MaximumHappyVertices::GreedyMHV::colourAllVertices(const DataStructures::Graph* graph, const DataStructures::Colouring* initialColouring, DataStructures::MutableColouring* colouringToColour, DataStructures::ColourType colour)
{
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!initialColouring->isColoured(vertex))
        {
            colouringToColour->setColour(vertex, colour);
        }
    }
}
