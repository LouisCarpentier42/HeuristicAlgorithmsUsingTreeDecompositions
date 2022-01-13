//
// Created by louis on 14/11/2021.
//

#include "BasicMHVEvaluator.h"

int DataStructures::BasicMHVEvaluator::evaluate(const DataStructures::Graph* graph) const
{
    int nbHappyVertices{0};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!graph->isColoured(vertex)) continue;
        bool vertexIsHappy{true};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (graph->getColour(neighbour) != graph->getColour(vertex))
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
{
//    int nbHappyVertices{startEvaluation};
//    for (DataStructures::VertexType vertex : recolouredVertices)
//    {
//        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
//        {
//
//        }
//    }
//    return nbHappyVertices;
    return 0; // TODO
}
