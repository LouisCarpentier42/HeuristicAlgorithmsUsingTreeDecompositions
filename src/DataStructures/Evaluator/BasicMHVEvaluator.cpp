//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include <algorithm>
#include "BasicMHVEvaluator.h"

int DataStructures::BasicMHVEvaluator::evaluate(const std::shared_ptr<Graph>& graph) const
{
    int nbHappyVertices{0};
    for (VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!graph->isColoured(vertex)) continue;

        bool vertexIsHappy{true};
        for (VertexType neighbour : graph->getNeighbours(vertex))
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
        // Remove the happy vertices from the old colour assignments
        for (std::shared_ptr<ColourAssignment>& oldColourAssignment : oldColourAssignments)
        {
            if (isHappy(vertex, oldColourAssignment, graph))
                evaluation -= 1;
        }

        // Check if the vertex is happy in the new colour assignment
        if (isHappy(vertex, newColourAssignment, graph))
            evaluation += 1;
    }

    // Return the adjusted evaluation
    return evaluation;
}

bool DataStructures::BasicMHVEvaluator::isHappy(
        VertexType vertex,
        std::shared_ptr<ColourAssignment>& colourAssignments,
        const std::shared_ptr<Graph>& graph)
{
    return (
        colourAssignments->isColoured(vertex)
        &&
        std::all_of(
           graph->getNeighbours(vertex).begin(),
           graph->getNeighbours(vertex).end(),
           [colourAssignments, vertex](auto neighbour){ return colourAssignments->getColour(vertex) == colourAssignments->getColour(neighbour); }
        )
    );
}
