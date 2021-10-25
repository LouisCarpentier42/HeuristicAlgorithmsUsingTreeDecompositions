//
// Created by louis on 25/10/2021.
//

#include "GreedyMHV.h"

MaximumHappyVertices::Colouring* MaximumHappyVertices::GreedyMHV::solve()
{
    Colouring* bestColouring{nullptr};
    unsigned int maxNbHappyVertices{0};
    for (colourType colour{1}; colour<colouring->getNbColours(); colour++)
    {
        MaximumHappyVertices::Colouring* newColouring{nullptr}; // TODO make a copy of the colouring
        colourAllVertices(newColouring, colour);
        if (getNbHappyVertices(graph, newColouring) > maxNbHappyVertices)
        {
            bestColouring = newColouring;
            maxNbHappyVertices = getNbHappyVertices(graph, newColouring);
        }
    }
    return bestColouring;
}

void MaximumHappyVertices::GreedyMHV::colourAllVertices(
        MaximumHappyVertices::Colouring *colouring,
        colourType colour)
{
    for (vertexType vertex{0}; vertex<graph->getNbVertices(); vertex++)
    {
        if (!colouring->isPrecoloured(vertex))
        {
            colouring->setColour(vertex, colour);
        }
    }
}