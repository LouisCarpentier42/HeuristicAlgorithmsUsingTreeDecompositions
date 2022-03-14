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

        [[nodiscard]] int evaluate(const std::shared_ptr<Graph>& graph) const override;

        [[nodiscard]] int evaluate(
            const std::set<VertexType>& recolouredVertices,
            std::vector<std::shared_ptr<ColourAssignment>>& oldColourAssignments,
            std::shared_ptr<ColourAssignment>& newColourAssignment,
            const std::shared_ptr<Graph>& graph,
            int startEvaluation
        ) const override;

    private:
        [[nodiscard]] static bool isHappy(
            VertexType vertex,
            std::shared_ptr<ColourAssignment>& colourAssignments,
            const std::shared_ptr<DataStructures::Graph>& graph
        );
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BASICMHVEVALUATOR_H
