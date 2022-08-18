//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H

#include "../DataStructures/Evaluator/Evaluator.h"
#include "../DataStructures/Graph/Graph.h"

#include <memory>

namespace Solvers
{
    class SolverBase
    {
    public:
        const std::unique_ptr<DataStructures::Evaluator> evaluator;

        explicit SolverBase(std::unique_ptr<DataStructures::Evaluator> evaluator) : evaluator{std::move(evaluator)} {}

        virtual void solve(std::shared_ptr<DataStructures::Graph>& graph) const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H
