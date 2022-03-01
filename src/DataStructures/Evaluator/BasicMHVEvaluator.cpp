//
// Created by louis on 14/11/2021.
//

#include <algorithm>
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
        // Remove the happy vertices from the old colour assignments
        for (DataStructures::ColourAssignments* oldColourAssignment : oldColourAssignments)
        {
            if (isHappy(vertex, oldColourAssignment, graph))
                evaluation -= 1;
        }

        // Check if the vertex is happy in the new colour assignment
        if (isHappy(vertex, newColourAssignments, graph))
            evaluation += 1;

    }

    // Return the adjusted evaluation
    return evaluation;
}

bool DataStructures::BasicMHVEvaluator::isHappy(
        DataStructures::VertexType vertex,
        DataStructures::ColourAssignments* colourAssignments,
        const DataStructures::Graph *graph)
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
