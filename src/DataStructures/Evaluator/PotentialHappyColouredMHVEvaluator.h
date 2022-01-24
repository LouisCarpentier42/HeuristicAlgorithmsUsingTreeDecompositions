//
// Created by louis on 18/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYCOLOUREDMHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYCOLOUREDMHVEVALUATOR_H

#include "Evaluator.h"

namespace DataStructures
{
    class PotentialHappyColouredMHVEvaluator : public Evaluator
    {
    private:
        const int happyVertexWeight;
        const int potentiallyHappyVertexWeight;
        const int unhappyVertexWeight;

    public:
        PotentialHappyColouredMHVEvaluator(
            int happyVertexWeight,
            int potentiallyHappyVertexWeight,
            int unhappyVertexWeight
        );

        [[nodiscard]] int evaluate(const DataStructures::Graph* graph) const override;

        [[nodiscard]] int evaluate(
            const std::vector<DataStructures::VertexType>& recolouredVertices,
            const DataStructures::TableEntry::ColourAssignments& colourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation
        ) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYCOLOUREDMHVEVALUATOR_H
