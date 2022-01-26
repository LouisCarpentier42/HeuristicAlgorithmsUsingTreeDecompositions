//
// Created by louis on 10/12/2021.
//

#include "PotentialHappyUncolouredMHVEvaluator.h"

#include <set>

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
    std::set<DataStructures::VertexType> newlyHappyColouredVertices{};
    std::set<DataStructures::VertexType> newlyUnhappyColouredVertices{};
    std::set<DataStructures::VertexType> newlyPotentiallyHappyColouredVertices{};
    std::set<DataStructures::VertexType> notPotentiallyHappyColouredAnymoreVertices{};
    std::set<DataStructures::VertexType> newlyHappyUncolouredVertices{};
    std::set<DataStructures::VertexType> newlyUnhappyUncolouredVertices{};
    std::set<DataStructures::VertexType> newlyPotentiallyHappyUncolouredVertices{};
    std::set<DataStructures::VertexType> notHappyUncolouredAnymoreVertices{};
    std::set<DataStructures::VertexType> notUnhappyUncolouredAnymoreVertices{};
    std::set<DataStructures::VertexType> notPotentiallyHappyUncolouredAnymoreVertices{};
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

            if (checkedNeighbours.find(neighbour) == checkedNeighbours.end())
            {
                if (colourAssignments.isColoured(neighbour))
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
                        else if (colourAssignments.getColour(neighbour) != colourAssignments.getColour(neighbourOfNeighbour))
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
                            notPotentiallyHappyColouredAnymoreVertices.insert(neighbour);
                            newlyUnhappyColouredVertices.insert(neighbour);
                        }
                    }
                    else
                    {
                        notPotentiallyHappyColouredAnymoreVertices.insert(neighbour);
                        if (colourAssignments.getColour(neighbour) == colourAssignments.getColour(vertex))
                        {
                            newlyHappyColouredVertices.insert(neighbour);
                        }
                        else
                        {
                            newlyUnhappyColouredVertices.insert(neighbour);
                        }
                    }
                }
                else
                {
                    ColourType colourNeighboursOfNeighbour{0};
                    bool neighbourIsUnhappy{false};
                    bool neighbourHasUncolouredNeighbour{false};
                    for (DataStructures::VertexType neighbourOfNeighbour : graph->getNeighbours(neighbour))
                    {
                        if (neighbourOfNeighbour == vertex) continue;

                        if (!colourAssignments.isColoured(neighbourOfNeighbour))
                        {
                            neighbourHasUncolouredNeighbour = true;
                        }
                        else if (colourNeighboursOfNeighbour == 0 && colourAssignments.isColoured(neighbourOfNeighbour))
                        {
                            colourNeighboursOfNeighbour = colourAssignments.getColour(neighbourOfNeighbour);
                        }
                        else if (colourNeighboursOfNeighbour != 0 && colourAssignments.isColoured(colourNeighboursOfNeighbour) && colourAssignments.getColour(neighbour) != colourNeighboursOfNeighbour)
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
                        if (colourNeighboursOfNeighbour == 0)
                        {
                            newlyPotentiallyHappyUncolouredVertices.insert(neighbour);
                        }
                        else if (colourNeighboursOfNeighbour != colourAssignments.getColour(vertex))
                        {
                            notPotentiallyHappyUncolouredAnymoreVertices.insert(neighbour);
                            newlyUnhappyUncolouredVertices.insert(neighbour);
                        }
                    }
                    else
                    {
                        notPotentiallyHappyUncolouredAnymoreVertices.insert(neighbour);
                        if (colourNeighboursOfNeighbour == colourAssignments.getColour(vertex))
                        {
                            newlyHappyUncolouredVertices.insert(neighbour);
                        }
                        else
                        {
                            newlyUnhappyUncolouredVertices.insert(neighbour);
                        }
                    }
                }
                checkedNeighbours.insert(neighbour);
            }
        }

        if (vertexIsUnhappy)
        {
            newlyUnhappyColouredVertices.insert(vertex);
            notUnhappyUncolouredAnymoreVertices.insert(vertex);
        }
        else if (hasUncolouredNeighbour)
        {
            newlyPotentiallyHappyColouredVertices.insert(vertex);
            notPotentiallyHappyUncolouredAnymoreVertices.insert(vertex);
        }
        else
        {
            newlyHappyColouredVertices.insert(vertex);
            notUnhappyUncolouredAnymoreVertices.insert(vertex);
        }
    }

    return startEvaluation +
           happyColouredVertexWeight * newlyHappyColouredVertices.size() +
           unhappyColouredVertexWeight * newlyUnhappyColouredVertices.size() +
           potentiallyHappyColouredVertexWeight * (newlyPotentiallyHappyColouredVertices.size() - notPotentiallyHappyColouredAnymoreVertices.size()) +
           happyUncolouredVertexWeight * (newlyHappyUncolouredVertices.size() - notHappyUncolouredAnymoreVertices.size())+
           unhappyUncolouredVertexWeight * (newlyUnhappyUncolouredVertices.size() - notUnhappyUncolouredAnymoreVertices.size()) +
           potentiallyHappyUncolouredVertexWeight * (newlyPotentiallyHappyUncolouredVertices.size() - notPotentiallyHappyUncolouredAnymoreVertices.size());
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
