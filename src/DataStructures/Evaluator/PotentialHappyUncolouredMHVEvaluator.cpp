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

int DataStructures::PotentialHappyUncolouredMHVEvaluator::evaluate(const DataStructures::Graph *graph) const
{
    int evaluation{0};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (graph->isColoured(vertex))
            evaluation += getWeightColouredVertex(vertex, graph);
        else
            evaluation += getWeightUncolouredVertex(vertex, graph);
    }
    return evaluation;
}

int DataStructures::PotentialHappyUncolouredMHVEvaluator::evaluate(
        const std::vector<DataStructures::VertexType>& recolouredVertices,
        const DataStructures::TableEntry::ColourAssignments& colourAssignments,
        const DataStructures::Graph *graph,
        int startEvaluation) const
{
    // TODO
    return 0;
}

int DataStructures::PotentialHappyUncolouredMHVEvaluator::getWeightColouredVertex(
        const DataStructures::VertexType colouredVertex,
        const DataStructures::Graph* graph) const
{
    bool hasUncolouredNeighbour{false};
    for (DataStructures::VertexType neighbour : graph->getNeighbours(colouredVertex))
    {
        if (!graph->isColoured(neighbour))
        {
            hasUncolouredNeighbour = true;
        }
        else if (graph->getColour(neighbour) != graph->getColour(colouredVertex))
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
        const DataStructures::Graph* graph) const
{
    ColourType colourNeighbours{0};
    bool hasUncolouredNeighbour{false};
    for (DataStructures::VertexType neighbour : graph->getNeighbours(uncolouredVertex))
    {
        if (!graph->isColoured(neighbour))
        {
            hasUncolouredNeighbour = true;
        }
        else if (colourNeighbours == 0 && graph->isColoured(neighbour))
        {
            colourNeighbours = graph->getColour(neighbour);
        }
        else if (colourNeighbours != 0 && graph->isColoured(neighbour) && graph->getColour(neighbour) != colourNeighbours)
        {
            return unhappyUncolouredVertexWeight;
        }
    }
    if (hasUncolouredNeighbour)
        return potentiallyHappyUncolouredVertexWeight;
    else
        return happyUncolouredVertexWeight;
}
