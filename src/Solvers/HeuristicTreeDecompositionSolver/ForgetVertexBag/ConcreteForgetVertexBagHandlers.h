//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETVERTEXBAGHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETVERTEXBAGHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class BasicForgetVertexBagHandler : public ForgetVertexBagHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETVERTEXBAGHANDLERS_H
