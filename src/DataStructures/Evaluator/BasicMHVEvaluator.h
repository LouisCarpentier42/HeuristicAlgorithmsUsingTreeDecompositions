//
// Created by louis on 14/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BASICMHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BASICMHVEVALUATOR_H

#include "Evaluator.h"

namespace DataStructures
{
    class BasicMHVEvaluator : public Evaluator
    {
    public:

        [[nodiscard]] int evaluate(const DataStructures::Graph* graph) const override;

        [[nodiscard]] int evaluate(
            const std::vector<DataStructures::VertexType>& recolouredVertices,
            const std::vector<DataStructures::ColourAssignments>& oldColourAssignments,
            const DataStructures::ColourAssignments& newColourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation
        ) const override;

    private:
        [[nodiscard]] static bool isHappy(
            DataStructures::VertexType vertex,
            const DataStructures::ColourAssignments& colourAssignments,
            const DataStructures::Graph* graph
        );
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BASICMHVEVALUATOR_H
