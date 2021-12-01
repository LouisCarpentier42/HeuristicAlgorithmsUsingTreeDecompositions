//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETELEAFNODEHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETELEAFNODEHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class PassiveLeafNodeHandlers : public LeafNodeHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleLeafNode(const DataStructures::LeafNode* node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETELEAFNODEHANDLERS_H
