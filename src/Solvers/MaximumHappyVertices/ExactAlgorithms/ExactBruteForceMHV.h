//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTBRUTEFORCEMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTBRUTEFORCEMHV_H

#include "../../SolverBase.h"

namespace MaximumHappyVertices
{
    class ExactBruteForceMHV : public Solvers::SolverBase
    {
    public:
        ExactBruteForceMHV();
        void solve(std::shared_ptr<DataStructures::Graph>& graph) const override;
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTBRUTEFORCEMHV_H
