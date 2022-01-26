//
// Created by louis on 18/11/2021.
//

#include "PotentialHappyColouredMHVEvaluator.h"

#include <set>

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
    std::set<DataStructures::VertexType> newlyHappyVertices{};
    std::set<DataStructures::VertexType> newlyUnhappyVertices{};
    std::set<DataStructures::VertexType> newlyPotentiallyHappyVertices{};
    std::set<DataStructures::VertexType> notPotentiallyHappyAnymoreVertices{};
    std::set<DataStructures::VertexType> checkedNeighbours{recolouredVertices.begin(), recolouredVertices.end()};

    for (DataStructures::VertexType vertex : recolouredVertices)
    {
        bool vertexIsUnhappy{false};
        bool hasUncolouredNeighbour{false};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!colourAssignments.isColoured(neighbour))
            {
                hasUncolouredNeighbour = true;
            }
            else if (colourAssignments.getColour(neighbour) != colourAssignments.getColour(vertex))
            {
                vertexIsUnhappy = true;
            }

            if (colourAssignments.isColoured(neighbour) && checkedNeighbours.find(neighbour) == checkedNeighbours.end())
            {
                bool neighbourIsUnhappy{false};
                bool neighbourHasUncolouredNeighbour{false};
                for (DataStructures::VertexType neighbourOfNeighbour : graph->getNeighbours(neighbour))
                {
                    if (neighbourOfNeighbour == vertex) continue;

                    if (!colourAssignments.isColoured(neighbourOfNeighbour))
                    {
                        neighbourHasUncolouredNeighbour = true;
                    }
                    else if (colourAssignments.getColour(neighbourOfNeighbour) != colourAssignments.getColour(neighbour))
                    {
                        neighbourIsUnhappy = true;
                        break;
                    }
                }
                if (neighbourIsUnhappy)
                {
                    // If the neighbour is unhappy without taking the newly coloured vertex
                    // into account, then it was already unhappy and nothing needs to change
                }
                else if (neighbourHasUncolouredNeighbour)
                {
                    // The neighbour was already potentially happy without taking vertex into account
                    if (colourAssignments.getColour(neighbour) != colourAssignments.getColour(vertex))
                    {
                        notPotentiallyHappyAnymoreVertices.insert(neighbour);
                        newlyUnhappyVertices.insert(neighbour);
                    }
                }
                else
                {
                    notPotentiallyHappyAnymoreVertices.insert(neighbour);
                    if (colourAssignments.getColour(neighbour) == colourAssignments.getColour(vertex))
                    {
                        newlyHappyVertices.insert(neighbour);
                    }
                    else
                    {
                        newlyUnhappyVertices.insert(neighbour);
                    }
                }
                checkedNeighbours.insert(neighbour);
            }
        }

        if (vertexIsUnhappy)
        {
            newlyUnhappyVertices.insert(vertex);
        }
        else if (hasUncolouredNeighbour)
        {
            newlyPotentiallyHappyVertices.insert(vertex);
        }
        else
        {
            newlyHappyVertices.insert(vertex);
        }
    }

    return startEvaluation +
           happyVertexWeight * newlyHappyVertices.size() +
           unhappyVertexWeight * newlyUnhappyVertices.size() +
           potentiallyHappyVertexWeight * (newlyPotentiallyHappyVertices.size() - notPotentiallyHappyAnymoreVertices.size());
}