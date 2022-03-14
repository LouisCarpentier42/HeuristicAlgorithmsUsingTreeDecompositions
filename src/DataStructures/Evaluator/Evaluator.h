//
// Created by louis on 14/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EVALUATOR_H

#include "../Graph/Graph.h"
#include "../DynamicProgramming/TableEntry.h"

#include <set>

namespace DataStructures
{
    class Evaluator
    {
    public:
        /**
         * Evaluate the colours of the given graph.
         *
         * @param graph The graph to evaluate the colours of.
         *
         * @return An evalatuion value for the vertices in the graph.
         */
        [[nodiscard]] virtual int evaluate(const std::shared_ptr<Graph>& graph) const = 0;

        [[nodiscard]] virtual int evaluate(
            const std::set<VertexType>& recolouredVertices,
            std::vector<std::shared_ptr<ColourAssignment>>& oldColourAssignments,
            std::shared_ptr<ColourAssignment>& newColourAssignment,
            const std::shared_ptr<Graph>& graph,
            int startEvaluation
        ) const = 0;
        [[nodiscard]] virtual int evaluate(
                const std::set<VertexType>& recolouredVertices,
                std::shared_ptr<ColourAssignment>& oldColourAssignment,
                std::shared_ptr<ColourAssignment>& newColourAssignment,
                const std::shared_ptr<Graph>& graph,
                int startEvaluation
        ) const;
        [[nodiscard]] virtual int evaluate(
            const VertexType& recolouredVertex,
            std::vector<std::shared_ptr<ColourAssignment>>& oldColourAssignments,
            std::shared_ptr<ColourAssignment>& newColourAssignment,
            const std::shared_ptr<Graph>& graph,
            int startEvaluation
        ) const;
        [[nodiscard]] virtual int evaluate(
            const VertexType& recolouredVertex,
            std::shared_ptr<ColourAssignment>& oldColourAssignment,
            std::shared_ptr<ColourAssignment>& newColourAssignment,
            const std::shared_ptr<Graph>& graph,
            int startEvaluation
        ) const;

    protected:
        [[nodiscard]] static std::set<VertexType> verticesAtDistance(
            size_t distance,
            const std::set<VertexType>& vertices,
            const std::shared_ptr<Graph>& graph
        );

    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EVALUATOR_H
