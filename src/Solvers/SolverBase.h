//
// Created by louis on 25/10/2021.
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
