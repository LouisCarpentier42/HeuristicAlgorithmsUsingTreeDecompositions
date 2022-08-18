//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H

#include "../../DataStructures/Graph/Graph.h"
#include "../../DataStructures/Evaluator/BasicMHVEvaluator.h"
#include "../SolverBase.h"

namespace MaximumHappyVertices
{
    class MaximumHappyVerticesSolver : public Solvers::SolverBase
    {
    public:
        MaximumHappyVerticesSolver()
            : Solvers::SolverBase{std::make_unique<DataStructures::BasicMHVEvaluator>()} {}
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H
