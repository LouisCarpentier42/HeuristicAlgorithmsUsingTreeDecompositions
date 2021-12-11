//
// Created by louis on 25/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H

#include "../DataStructures/Colouring/Colouring.h"
#include "../DataStructures/ColouringEvaluator/ColouringEvaluator.h"
#include "../DataStructures/Colouring/MutableColouring.h"
#include "../DataStructures/Graph/Graph.h"

namespace Solvers
{
    class SolverBase
    {
    public:
        const DataStructures::ColouringEvaluator* evaluator;

        explicit SolverBase(const DataStructures::ColouringEvaluator* evaluator) : evaluator{evaluator} {}

        [[nodiscard]] virtual DataStructures::Colouring* solve(
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring
        ) const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERBASE_H
