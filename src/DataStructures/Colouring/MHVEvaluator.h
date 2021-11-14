//
// Created by louis on 14/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MHVEVALUATOR_H

#include "ColouringEvaluator.h"

namespace DataStructures
{
    class MHVEvaluator : public ColouringEvaluator
    {
    public:
        explicit MHVEvaluator(const DataStructures::Graph* graph);

        [[nodiscard]] int evaluate(const DataStructures::Colouring* colouring) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MHVEVALUATOR_H
