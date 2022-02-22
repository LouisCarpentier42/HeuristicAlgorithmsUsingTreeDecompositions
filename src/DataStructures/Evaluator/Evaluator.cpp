//
// Created by louis on 22/02/2022.
//

#include "Evaluator.h"

int DataStructures::Evaluator::evaluate(
        const std::vector<DataStructures::VertexType>& recolouredVertices,
        const DataStructures::ColourAssignments& oldColourAssignments,
        const DataStructures::ColourAssignments& newColourAssignments,
        const DataStructures::Graph* graph,
        int startEvaluation) const
{
    return evaluate(
            recolouredVertices,
            std::vector<DataStructures::ColourAssignments>{oldColourAssignments},
            newColourAssignments,
            graph,
            startEvaluation);
}

int DataStructures::Evaluator::evaluate(
        const DataStructures::VertexType& recolouredVertex,
        const std::vector<DataStructures::ColourAssignments>& oldColourAssignments,
        const DataStructures::ColourAssignments& newColourAssignments,
        const DataStructures::Graph* graph,
        int startEvaluation) const
{
    return evaluate(
            std::vector<VertexType>{recolouredVertex},
            oldColourAssignments,
            newColourAssignments,
            graph,
            startEvaluation);
}

int DataStructures::Evaluator::evaluate(
        const DataStructures::VertexType& recolouredVertex,
        const DataStructures::ColourAssignments& oldColourAssignments,
        const DataStructures::ColourAssignments& newColourAssignments,
        const DataStructures::Graph* graph,
        int startEvaluation) const
{
    return evaluate(
            std::vector<VertexType>{recolouredVertex},
            std::vector<DataStructures::ColourAssignments>{oldColourAssignments},
            newColourAssignments,
            graph,
            startEvaluation);
}

std::set<DataStructures::VertexType> DataStructures::Evaluator::verticesAtDistance(
        size_t distance,
        const std::vector<DataStructures::VertexType>& vertices,
        const DataStructures::Graph* graph)
{
    // Initialise variables
    std::set<DataStructures::VertexType> neighbourhood{};
    std::set<DataStructures::VertexType> verticesToCheck{vertices.begin(), vertices.end()};

    // Neighbourhood at distance 0 to distance (distance-1)
    for (size_t currentDistance{0}; currentDistance < distance; currentDistance++)
    {
        std::set<DataStructures::VertexType> nextVerticesToCheck{};
        for (DataStructures::VertexType vertexToCheck : verticesToCheck)
        {
            auto pair = neighbourhood.insert(vertexToCheck);
            if (pair.second)
            {
                nextVerticesToCheck.insert(
                    graph->getNeighbours(vertexToCheck).begin(),
                    graph->getNeighbours(vertexToCheck).end()
                );
            }
        }
        verticesToCheck = nextVerticesToCheck;
    }

    // At the last distance, you don't need to do any computations for neighbouring vertices
    neighbourhood.insert(
        verticesToCheck.begin(),
        verticesToCheck.end()
    );

    return neighbourhood;
}


