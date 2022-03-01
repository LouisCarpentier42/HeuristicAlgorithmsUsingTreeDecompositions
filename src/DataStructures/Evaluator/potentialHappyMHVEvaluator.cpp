//
// Created by louis on 18/11/2021.
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

int DataStructures::potentialHappyMHVEvaluator::evaluate(const DataStructures::Graph* graph) const
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
            evaluation += potentialHappyVertexWeight;
        else
            evaluation += happyVertexWeight;
    }
    return evaluation;
}

int DataStructures::potentialHappyMHVEvaluator::evaluate(
        const std::set<DataStructures::VertexType>& recolouredVertices,
        std::vector<DataStructures::ColourAssignments*> oldColourAssignments,
        DataStructures::ColourAssignments* newColourAssignments,
        const DataStructures::Graph* graph,
        int startEvaluation) const
{
    int evaluation{startEvaluation};
    std::set<DataStructures::VertexType> potentiallyChangedVertices = verticesAtDistance(1, recolouredVertices, graph);

    // Check for all vertices how their happiness has changed
    for (DataStructures::VertexType vertex : potentiallyChangedVertices)
    {
        // Remove the evaluation from the old colour assignment
        for (DataStructures::ColourAssignments* oldColourAssignment : oldColourAssignments)
            evaluation -= getVertexWeight(vertex, oldColourAssignment, graph);

        // Add the evaluation from the new colour assignment
        evaluation += getVertexWeight(vertex, newColourAssignments, graph);
    }

    return evaluation;
}

int DataStructures::potentialHappyMHVEvaluator::getVertexWeight(
        DataStructures::VertexType vertex,
        DataStructures::ColourAssignments* colourAssignments,
        const DataStructures::Graph* graph) const
{
    if (!colourAssignments->isColoured(vertex))
    {
        ColourType oldColourNeighbours{0};
        bool hadColouredNeighbours{false};
        bool vertexWasUnhappy{false};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!colourAssignments->isColoured(neighbour))
            {
                // Nothing needs to happen for an uncoloured neighbour of an uncoloured vertex
            }
            else if (oldColourNeighbours == 0)
            {
                oldColourNeighbours = colourAssignments->getColour(neighbour);
                hadColouredNeighbours = true;
            }
            else if (colourAssignments->getColour(neighbour) != oldColourNeighbours)
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
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!colourAssignments->isColoured(neighbour))
            {
                hadUncolouredNeighbour = true;
            }
            else if (colourAssignments->getColour(neighbour) != colourAssignments->getColour(vertex))
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
