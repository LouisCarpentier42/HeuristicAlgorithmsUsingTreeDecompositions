//
// Created by louis on 10/12/2021.
//

#include "PotentialHappyUncolouredMHVEvaluator.h"

DataStructures::PotentialHappyUncolouredMHVEvaluator::PotentialHappyUncolouredMHVEvaluator(
        int happyColouredVertexWeight,
        int happyUncolouredVertexWeight,
        int potentiallyHappyColouredVertexWeight,
        int potentiallyHappyUncolouredVertexWeight,
        int unhappyColouredVertexWeight,
        int unhappyUncolouredVertexWeight)
    : happyColouredVertexWeight{happyColouredVertexWeight},
      happyUncolouredVertexWeight{happyUncolouredVertexWeight},
      potentiallyHappyColouredVertexWeight{potentiallyHappyColouredVertexWeight},
      potentiallyHappyUncolouredVertexWeight{potentiallyHappyUncolouredVertexWeight},
      unhappyColouredVertexWeight{unhappyColouredVertexWeight},
      unhappyUncolouredVertexWeight{unhappyUncolouredVertexWeight}
{ }

int DataStructures::PotentialHappyUncolouredMHVEvaluator::evaluate(
        const DataStructures::Graph *graph,
        const DataStructures::Colouring *colouring) const
{
    int evaluation{0};
    for (DataStructures::VertexType vertex{0}; vertex < colouring->getNbVertices(); vertex++)
    {
        if (colouring->isColoured(vertex))
            evaluation += getWeightColouredVertex(vertex, graph, colouring);
        else
            evaluation += getWeightUncolouredVertex(vertex, graph, colouring);
    }
    return evaluation;
}

int DataStructures::PotentialHappyUncolouredMHVEvaluator::getWeightColouredVertex(
        const DataStructures::VertexType colouredVertex,
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring) const
{
    bool hasUncolouredNeighbour{false};
    for (DataStructures::VertexType neighbour : *graph->getNeighbours(colouredVertex))
    {
        if (!colouring->isColoured(neighbour))
        {
            hasUncolouredNeighbour = true;
        }
        else if (colouring->getColour(neighbour) != colouring->getColour(colouredVertex))
        {
            return unhappyColouredVertexWeight;
        }
    }

    if (hasUncolouredNeighbour)
        return potentiallyHappyColouredVertexWeight;
    else
        return happyColouredVertexWeight;
}

int DataStructures::PotentialHappyUncolouredMHVEvaluator::getWeightUncolouredVertex(
        const DataStructures::VertexType uncolouredVertex,
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring) const
{
    ColourType colourNeighbours{0};
    bool hasUncolouredNeighbour{false};
    for (DataStructures::VertexType neighbour : *graph->getNeighbours(uncolouredVertex))
    {
        if (!colouring->isColoured(neighbour))
        {
            hasUncolouredNeighbour = true;
        }
        else if (colourNeighbours != 0 && colouring->getColour(neighbour) != colourNeighbours)
        {
            return unhappyUncolouredVertexWeight;
        }
        else
        {
            colourNeighbours = colouring->getColour(neighbour);
        }
    }
    if (hasUncolouredNeighbour)
        return potentiallyHappyUncolouredVertexWeight;
    else
        return happyUncolouredVertexWeight;
}
