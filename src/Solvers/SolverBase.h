//
// Created by louis on 25/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H

#include "../DataStructures/Evaluator/Evaluator.h"
#include "../DataStructures/Graph/Graph.h"

namespace Solvers
{
    class SolverBase
    {
    public:
        const DataStructures::Evaluator* evaluator;

        explicit SolverBase(const DataStructures::Evaluator* evaluator) : evaluator{evaluator} {}

        virtual void solve(DataStructures::Graph* graph) const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H
