//
// Created by louis on 14/11/2021.
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
