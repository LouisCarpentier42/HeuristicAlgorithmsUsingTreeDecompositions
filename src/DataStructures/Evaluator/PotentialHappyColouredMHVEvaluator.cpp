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

int DataStructures::PotentialHappyColouredMHVEvaluator::evaluate(const DataStructures::Graph* graph) const
{
    int evaluation{0};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!graph->isColoured(vertex)) continue;

        bool vertexIsUnhappy{false};
        bool hasUncolouredNeighbour{false};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!graph->isColoured(neighbour))
            {
                hasUncolouredNeighbour = true;
            }
            else if (graph->getColour(neighbour) != graph->getColour(vertex))
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

int DataStructures::PotentialHappyColouredMHVEvaluator::evaluate(
        const std::vector<DataStructures::VertexType>& recolouredVertices,
        const DataStructures::TableEntry::ColourAssignments& colourAssignments,
        const DataStructures::Graph *graph,
        int startEvaluation) const
{
    // TODO
    return 0;
}