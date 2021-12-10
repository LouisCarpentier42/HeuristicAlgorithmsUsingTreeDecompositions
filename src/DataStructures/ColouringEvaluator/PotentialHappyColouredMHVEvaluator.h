//
// Created by louis on 18/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYCOLOUREDMHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYCOLOUREDMHVEVALUATOR_H

#include "ColouringEvaluator.h"

namespace DataStructures
{
    class PotentialHappyColouredMHVEvaluator : public ColouringEvaluator
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

        [[nodiscard]] int evaluate(
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring
        ) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYCOLOUREDMHVEVALUATOR_H
