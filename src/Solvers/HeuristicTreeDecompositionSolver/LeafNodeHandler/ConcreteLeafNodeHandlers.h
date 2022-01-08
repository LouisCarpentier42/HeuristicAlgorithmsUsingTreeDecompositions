//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETELEAFNODEHANDLER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETELEAFNODEHANDLER_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class PassiveLeafNodeHandlers : public LeafNodeHandler
    {
    public:
        void handleLeafNode(DataStructures::LeafNode* node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETELEAFNODEHANDLER_H
