//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINBAGHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINBAGHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

// TODO ideas for join bag:
//  - when merging the colourings, when they differ to much better to skip them
//  - if left colour and right colour give equal evaluation, try to maintain both
//  - order of vertices when they are coloured during merge
//  - Use the n best colourings (attention for uncoloured vertices for only one child)

namespace Solvers
{
    class BasicJoinBagHandler : public JoinBagHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleJoinBag(const DataStructures::JoinBag* bag) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINBAGHANDLERS_H
