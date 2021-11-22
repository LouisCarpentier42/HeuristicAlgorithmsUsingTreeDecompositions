//
// Created by louis on 25/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H

#include "../DataStructures/Colouring/Colouring.h"
#include "../DataStructures/Colouring/ColouringEvaluator.h"
#include "../DataStructures/Colouring/MutableColouring.h"
#include "../DataStructures/Graph/Graph.h"

namespace Solvers
{
    class SolverBase
    {
    public:
        const DataStructures::Colouring* colouring;
        const DataStructures::Graph* graph;
        const DataStructures::ColouringEvaluator* evaluator;

        SolverBase(const DataStructures::Graph* graph,
                   const DataStructures::Colouring* colouring,
                   const DataStructures::ColouringEvaluator* evaluator)
            : graph{graph}, colouring{colouring}, evaluator{evaluator} {}

        [[nodiscard]] virtual DataStructures::MutableColouring* solve() const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H