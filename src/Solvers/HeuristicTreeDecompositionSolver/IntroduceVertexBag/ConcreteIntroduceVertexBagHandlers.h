//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCEVERTEXBAGHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCEVERTEXBAGHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class BasicIntroduceVertexBagHandler : public IntroduceVertexBagHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag* bag) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCEVERTEXBAGHANDLERS_H
