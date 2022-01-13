//
// Created by louis on 25/10/2021.
//

#include "GreedyMHV.h"

void MaximumHappyVertices::GreedyMHV::solve(DataStructures::Graph* graph) const
{
    colourAllVertices(graph, 1);
    DataStructures::ColourType bestColour{1};
    int bestNbHappyVertices{evaluator->evaluate(graph)};

    for (DataStructures::ColourType colour{2}; colour <= graph->getNbColours(); colour++)
    {
        colourAllVertices(graph, colour);
        int nbHappyVertices{evaluator->evaluate(graph)};
        if (nbHappyVertices > bestNbHappyVertices)
        {
            bestColour = colour;
            bestNbHappyVertices = nbHappyVertices;
        }
    }
    colourAllVertices(graph, bestColour);
}

void MaximumHappyVertices::GreedyMHV::colourAllVertices(
        DataStructures::Graph* graph,
        DataStructures::ColourType colour)
{
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!graph->isPrecoloured(vertex))
        {
            graph->setColour(vertex, colour);
        }
    }
}
