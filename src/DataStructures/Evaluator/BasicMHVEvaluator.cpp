//
// Created by louis on 14/11/2021.
//

#include "BasicMHVEvaluator.h"

#include <set>

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
        const DataStructures::ColourAssignments& colourAssignments,
        const DataStructures::Graph *graph,
        int startEvaluation) const
{
    int evaluation{startEvaluation};
    // TODO probably not needed with checkedNeighboursArray -> needed but why?
    //  try to remove this set + also in the other evaluators
    std::set<DataStructures::VertexType> newlyHappyVertices{};
    std::set<DataStructures::VertexType> checkedNeighbours{recolouredVertices.begin(), recolouredVertices.end()};

    for (DataStructures::VertexType vertex : recolouredVertices)
    {
        bool vertexIsHappy{true};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!colourAssignments.isColoured(neighbour))
            {
                vertexIsHappy = false;
                continue;
            }

            if (checkedNeighbours.find(neighbour) == checkedNeighbours.end())
            {
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
                    newlyHappyVertices.insert(neighbour);
//                    evaluation++;
                }
                checkedNeighbours.insert(neighbour);
            }

            if (colourAssignments.getColour(neighbour) != colourAssignments.getColour(vertex))
            {
                vertexIsHappy = false;
            }
        }

        if (vertexIsHappy)
        {
            newlyHappyVertices.insert(vertex);
//            evaluation++;
        }
    }

//    return evaluation;
    return startEvaluation + newlyHappyVertices.size();
}
