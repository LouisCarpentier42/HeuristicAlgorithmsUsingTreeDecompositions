//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "potentialHappyMHVEvaluator.h"

DataStructures::potentialHappyMHVEvaluator::potentialHappyMHVEvaluator(
        int happyVertexWeight,
        int potentialHappyVertexWeight,
        int unhappyVertexWeight)
    : happyVertexWeight{happyVertexWeight},
      potentialHappyVertexWeight{potentialHappyVertexWeight},
      unhappyVertexWeight{unhappyVertexWeight}
{}

int DataStructures::potentialHappyMHVEvaluator::evaluate(const std::shared_ptr<Graph>& graph) const
{
    int evaluation{0};
    for (VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!graph->isColoured(vertex)) continue;

        bool vertexIsUnhappy{false};
        bool hasUncolouredNeighbour{false};
        for (VertexType neighbour : graph->getNeighbours(vertex))
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
            evaluation += potentialHappyVertexWeight;
        else
            evaluation += happyVertexWeight;
    }
    return evaluation;
}

int DataStructures::potentialHappyMHVEvaluator::evaluate(
        const std::set<VertexType>& recolouredVertices,
        std::vector<std::shared_ptr<ColourAssignment>>& oldColourAssignments,
        std::shared_ptr<ColourAssignment>& newColourAssignment,
        const std::shared_ptr<Graph>& graph,
        int startEvaluation) const
{
    int evaluation{startEvaluation};
    std::set<VertexType> potentiallyChangedVertices = verticesAtDistance(1, recolouredVertices, graph);

    // Check for all vertices how their happiness has changed
    for (VertexType vertex : potentiallyChangedVertices)
    {
        // Remove the evaluation from the old colour assignment
        for (std::shared_ptr<ColourAssignment>& oldColourAssignment : oldColourAssignments)
            evaluation -= getVertexWeight(vertex, oldColourAssignment, graph);

        // Add the evaluation from the new colour assignment
        evaluation += getVertexWeight(vertex, newColourAssignment, graph);
    }

    return evaluation;
}

int DataStructures::potentialHappyMHVEvaluator::getVertexWeight(
        VertexType vertex,
        std::shared_ptr<ColourAssignment>& colourAssignment,
        const std::shared_ptr<Graph>& graph) const
{
    if (!colourAssignment->isColoured(vertex))
    {
        ColourType oldColourNeighbours{0};
        bool hadColouredNeighbours{false};
        bool vertexWasUnhappy{false};
        for (VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!colourAssignment->isColoured(neighbour))
            {
                // Nothing needs to happen for an uncoloured neighbour of an uncoloured vertex
            }
            else if (oldColourNeighbours == 0)
            {
                oldColourNeighbours = colourAssignment->getColour(neighbour);
                hadColouredNeighbours = true;
            }
            else if (colourAssignment->getColour(neighbour) != oldColourNeighbours)
            {
                vertexWasUnhappy = true;
                break;
            }
        }

        if (vertexWasUnhappy)
            return unhappyVertexWeight;
        else if (hadColouredNeighbours) // && !vertexWasHappy
            return potentialHappyVertexWeight;
        else
            return 0;
    }
    else
    {
        bool vertexWasUnhappy{false};
        bool hadUncolouredNeighbour{false};
        for (VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!colourAssignment->isColoured(neighbour))
            {
                hadUncolouredNeighbour = true;
            }
            else if (colourAssignment->getColour(neighbour) != colourAssignment->getColour(vertex))
            {
                vertexWasUnhappy = true;
                break;
            }
        }

        if (vertexWasUnhappy)
            return unhappyVertexWeight;
        else if (hadUncolouredNeighbour) // && !vertexWasUnhappy
            return potentialHappyVertexWeight;
        else  // !vertexWasUnhappy && !hadUncolouredNeighbour
            return happyVertexWeight;
    }
}
