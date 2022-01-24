//
// Created by louis on 14/11/2021.
//

#include "BasicMHVEvaluator.h"
#include <iostream> // TODO remove

int DataStructures::BasicMHVEvaluator::evaluate(const DataStructures::Graph* graph) const
{
    int nbHappyVertices{0};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!graph->isColoured(vertex)) continue;
        bool vertexIsHappy{true};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!graph->isColoured(vertex) || graph->getColour(neighbour) != graph->getColour(vertex))
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

int DataStructures::BasicMHVEvaluator::evaluate(
        const std::vector<DataStructures::VertexType>& recolouredVertices,
        const DataStructures::TableEntry::ColourAssignments& colourAssignments,
        const DataStructures::Graph *graph,
        int startEvaluation) const
{ // TODO counts double when handling multiple recoloured vertices
    int nbHappyVertices{startEvaluation};
    for (DataStructures::VertexType vertex : recolouredVertices)
    {
        if (graph->isPrecoloured(vertex)) continue;
        bool vertexIsHappy{true};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!colourAssignments.isColoured(neighbour))
            {
                vertexIsHappy = false;
                continue;
            }

            bool neighbourIsHappy{true};
            for (DataStructures::VertexType neighbourOfNeighbour : graph->getNeighbours(neighbour))
            {
                if (!colourAssignments.isColoured(neighbourOfNeighbour)
                    || colourAssignments.getColour(neighbourOfNeighbour) != colourAssignments.getColour(neighbour))
                {
                    neighbourIsHappy = false;
                    break;
                }
            }
            if (neighbourIsHappy)
            {
                nbHappyVertices++;
            }

            if (colourAssignments.getColour(neighbour) != colourAssignments.getColour(vertex))
            {
                vertexIsHappy = false;
            }
        }

        if (vertexIsHappy)
        {
            nbHappyVertices++;
        }
    }
    return nbHappyVertices;
}
