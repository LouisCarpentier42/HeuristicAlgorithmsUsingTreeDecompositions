//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETELEAFBAGHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETELEAFBAGHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class ConcreteLeafBagHandlers : public LeafBagHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleLeafBag(const DataStructures::LeafBag* bag) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETELEAFBAGHANDLERS_H
