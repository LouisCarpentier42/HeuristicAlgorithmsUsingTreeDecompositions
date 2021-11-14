//
// Created by louis on 14/11/2021.
//

#include "MHVEvaluator.h"

DataStructures::MHVEvaluator::MHVEvaluator(const DataStructures::Graph& graph)
    : ColouringEvaluator(graph)
{}

int DataStructures::MHVEvaluator::evaluate(const DataStructures::Colouring *colouring) const
{
    int nbHappyVertices{0};
    for (DataStructures::VertexType vertex{0}; vertex < colouring->getNbVertices(); vertex++)
    {
        if (!colouring->isColoured(vertex)) continue;
        bool vertexIsHappy{true};
        for (DataStructures::VertexType neighbour : *graph.getNeighbours(vertex))
        {
            if (colouring->getColour(neighbour) != colouring->getColour(vertex))
            {
                vertexIsHappy = false;
                break;
            }
        }
        if (vertexIsHappy)
        {
            nbHappyVertices++;
        }
    }
    return nbHappyVertices;
}