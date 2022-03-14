//
// Created by louis on 22/02/2022.
//

#include "Evaluator.h"

int DataStructures::Evaluator::evaluate(
        const std::set<VertexType>& recolouredVertices,
        std::shared_ptr<ColourAssignment>& oldColourAssignment,
        std::shared_ptr<ColourAssignment>& newColourAssignment,
        const std::shared_ptr<Graph>& graph,
        int startEvaluation) const
{
    auto oldColourAssignments = std::vector<std::shared_ptr<ColourAssignment>>{oldColourAssignment};
    return evaluate(
            recolouredVertices,
            oldColourAssignments,
            newColourAssignment,
            graph,
            startEvaluation);
}

int DataStructures::Evaluator::evaluate(
        const VertexType& recolouredVertex,
        std::vector<std::shared_ptr<ColourAssignment>>& oldColourAssignments,
        std::shared_ptr<ColourAssignment>& newColourAssignment,
        const std::shared_ptr<Graph>& graph,
        int startEvaluation) const
{
    return evaluate(
            std::set<VertexType>{recolouredVertex},
            oldColourAssignments,
            newColourAssignment,
            graph,
            startEvaluation);
}

int DataStructures::Evaluator::evaluate(
        const VertexType& recolouredVertex,
        std::shared_ptr<ColourAssignment>& oldColourAssignment,
        std::shared_ptr<ColourAssignment>& newColourAssignment,
        const std::shared_ptr<Graph>& graph,
        int startEvaluation) const
{
    auto oldColourAssignments = std::vector<std::shared_ptr<ColourAssignment>>{oldColourAssignment};
    return evaluate(
            std::set<VertexType>{recolouredVertex},
            oldColourAssignments,
            newColourAssignment,
            graph,
            startEvaluation);
}

std::set<DataStructures::VertexType> DataStructures::Evaluator::verticesAtDistance(
        size_t distance,
        const std::set<VertexType>& vertices,
        const std::shared_ptr<Graph>& graph)
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


