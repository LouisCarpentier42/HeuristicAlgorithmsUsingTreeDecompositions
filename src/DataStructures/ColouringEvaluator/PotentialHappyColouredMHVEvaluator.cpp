//
// Created by louis on 18/11/2021.
//

#include "PotentialHappyColouredMHVEvaluator.h"

DataStructures::PotentialHappyColouredMHVEvaluator::PotentialHappyColouredMHVEvaluator(
        int happyVertexWeight,
        int potentiallyHappyVertexWeight,
        int unhappyVertexWeight)
    : happyVertexWeight{happyVertexWeight},
      potentiallyHappyVertexWeight{potentiallyHappyVertexWeight},
      unhappyVertexWeight{unhappyVertexWeight}
{}

int DataStructures::PotentialHappyColouredMHVEvaluator::evaluate(const DataStructures::Graph* graph, const DataStructures::Colouring *colouring) const
{
    int evaluation{0};
    for (DataStructures::VertexType vertex{0}; vertex < colouring->getNbVertices(); vertex++)
    {
        if (!colouring->isColoured(vertex)) continue;

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
