//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETNODEHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETNODEHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class PassiveForgetNodeHandler : public ForgetNodeHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleForgetVertexBag(const DataStructures::ForgetNode* node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETNODEHANDLERS_H
