//
// Created by louis on 14/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGEVALUATOR_H

#include "../Graph/Graph.h"
#include "../DynamicProgramming/TableEntry.h"

namespace DataStructures
{
    class ColouringEvaluator
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

        /**
         * Evaluate the given colour assignment.
         *
         * @param recolouredVertices The vertices that have been recoloured and thus could influence the evaluation.
         * @param colourAssignments The colour assignments of all vertices.
         * @param graph The graph that's used as context for the colourings.
         * @param startEvaluation The evaluation value to start from.
         *
         * @return A value indicating how well a given colour map is. A better colouring must receive
         *         a higher evaluation value.
         */
        [[nodiscard]] virtual int evaluate(
            const std::vector<DataStructures::VertexType>& recolouredVertices,
            const DataStructures::TableEntry::ColourAssignments& colourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation
        ) const = 0;

        [[nodiscard]] int evaluate(
            const DataStructures::VertexType& recolouredVertex,
            const DataStructures::TableEntry::ColourAssignments& colourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation) const
        { return evaluate(std::vector<VertexType>{recolouredVertex}, colourAssignments, graph, startEvaluation); }
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGEVALUATOR_H
