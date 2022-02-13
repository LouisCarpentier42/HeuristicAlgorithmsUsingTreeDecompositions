//
// Created by louis on 13/02/2022.
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
        void solve(DataStructures::Graph* graph) const override;
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTBRUTEFORCEMHV_H
