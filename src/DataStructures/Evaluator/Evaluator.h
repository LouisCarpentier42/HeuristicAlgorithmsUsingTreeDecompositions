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
        [[nodiscard]] virtual int evaluate(const DataStructures::Graph* graph) const = 0;

        [[nodiscard]] virtual int evaluate(
            const std::set<DataStructures::VertexType>& recolouredVertices,
            std::vector<DataStructures::ColourAssignments*> oldColourAssignments,
            DataStructures::ColourAssignments* newColourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation
        ) const = 0;
        [[nodiscard]] virtual int evaluate(
                const std::set<DataStructures::VertexType>& recolouredVertices,
                ColourAssignments* oldColourAssignments,
                DataStructures::ColourAssignments* newColourAssignments,
                const DataStructures::Graph* graph,
                int startEvaluation
        ) const;
        [[nodiscard]] virtual int evaluate(
            const DataStructures::VertexType& recolouredVertex,
            std::vector<DataStructures::ColourAssignments*>& oldColourAssignments,
            DataStructures::ColourAssignments* newColourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation
        ) const;
        [[nodiscard]] virtual int evaluate(
            const DataStructures::VertexType& recolouredVertex,
            DataStructures::ColourAssignments* oldColourAssignments,
            DataStructures::ColourAssignments* newColourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation
        ) const;

    protected:
        [[nodiscard]] static std::set<DataStructures::VertexType> verticesAtDistance(
            size_t distance,
            const std::set<DataStructures::VertexType>& vertices,
            const DataStructures::Graph* graph
        );

    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EVALUATOR_H
