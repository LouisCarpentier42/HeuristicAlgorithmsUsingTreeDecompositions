//
// Created by louis on 18/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_ADVANCEDMHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_ADVANCEDMHVEVALUATOR_H

#include "ColouringEvaluator.h"

namespace DataStructures
{
    class AdvancedMHVEvaluator : public ColouringEvaluator
    {
    private:
        const int happyVertexWeight;
        const int potentiallyHappyVertexWeight;
        const int unhappyVertexWeight;

    public:
        AdvancedMHVEvaluator(const DataStructures::Graph* graph,
                             int happyVertexWeight,
                             int potentiallyHappyVertexWeight,
                             int unhappyVertexWeight);

        [[nodiscard]] int evaluate(const DataStructures::Colouring* colouring) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_ADVANCEDMHVEVALUATOR_H
