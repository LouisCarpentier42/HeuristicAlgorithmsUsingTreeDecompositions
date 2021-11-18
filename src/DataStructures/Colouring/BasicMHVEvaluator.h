//
// Created by louis on 14/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BASICMHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BASICMHVEVALUATOR_H

#include "ColouringEvaluator.h"

namespace DataStructures
{
    class BasicMHVEvaluator : public ColouringEvaluator
    {
    public:
        explicit BasicMHVEvaluator(const DataStructures::Graph* graph);

        [[nodiscard]] int evaluate(const DataStructures::Colouring* colouring) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BASICMHVEVALUATOR_H
