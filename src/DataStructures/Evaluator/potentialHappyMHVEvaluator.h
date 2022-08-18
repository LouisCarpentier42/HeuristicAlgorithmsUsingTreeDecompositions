//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYMHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYMHVEVALUATOR_H

#include "Evaluator.h"

namespace DataStructures
{
    class potentialHappyMHVEvaluator : public Evaluator
    {
    private:
        const int happyVertexWeight;
        const int potentialHappyVertexWeight;
        const int unhappyVertexWeight;

    public:
        potentialHappyMHVEvaluator(
            int happyVertexWeight,
            int potentialHappyVertexWeight,
            int unhappyVertexWeight
        );

        [[nodiscard]] int evaluate(const std::shared_ptr<Graph>& graph) const override;

        [[nodiscard]] int evaluate(
            const std::set<VertexType>& recolouredVertices,
            std::vector<std::shared_ptr<ColourAssignment>>& oldColourAssignments,
            std::shared_ptr<ColourAssignment>& newColourAssignment,
            const std::shared_ptr<Graph>& graph,
            int startEvaluation
        ) const override;

    private:
        [[nodiscard]] int getVertexWeight(
            VertexType vertex,
            std::shared_ptr<ColourAssignment>& colourAssignment,
            const std::shared_ptr<Graph>& graph
        ) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYMHVEVALUATOR_H
