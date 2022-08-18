//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "GreedyMHV.h"

void MaximumHappyVertices::GreedyMHV::solve(std::shared_ptr<DataStructures::Graph>& graph) const
{
    colourAllVertices(graph, 1);
    DataStructures::ColourType bestColour{1};
    if (evaluator == nullptr)
        std::cout << "evaluator is nullptr in solve greedy\n";
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
        std::shared_ptr<DataStructures::Graph>& graph,
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
