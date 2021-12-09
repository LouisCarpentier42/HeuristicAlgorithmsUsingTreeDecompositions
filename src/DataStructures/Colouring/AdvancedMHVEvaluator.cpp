//
// Created by louis on 18/11/2021.
//

#include "AdvancedMHVEvaluator.h"

DataStructures::AdvancedMHVEvaluator::AdvancedMHVEvaluator(
        int happyVertexWeight,
        int potentiallyHappyVertexWeight,
        int unhappyVertexWeight)
    : happyVertexWeight{happyVertexWeight},
      potentiallyHappyVertexWeight{potentiallyHappyVertexWeight},
      unhappyVertexWeight{unhappyVertexWeight}
{}

int DataStructures::AdvancedMHVEvaluator::evaluate(const DataStructures::Graph* graph, const DataStructures::Colouring *colouring) const
{
    int evaluation{0};
    for (DataStructures::VertexType vertex{0}; vertex < colouring->getNbVertices(); vertex++)
    {
        if (!colouring->isColoured(vertex)) continue; // TODO also check uncoloured vertices

        bool vertexIsUnhappy{false};
        bool hasUncolouredNeighbour{false};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (!colouring->isColoured(neighbour))
            {
                hasUncolouredNeighbour = true;
            }
            else if (colouring->getColour(neighbour) != colouring->getColour(vertex))
            {
                vertexIsUnhappy = true;
                break;
            }
        }

        if (vertexIsUnhappy)
            evaluation += unhappyVertexWeight;
        else if (hasUncolouredNeighbour)
            evaluation += potentiallyHappyVertexWeight;
        else
            evaluation += happyVertexWeight;
    }
    return evaluation;
}
