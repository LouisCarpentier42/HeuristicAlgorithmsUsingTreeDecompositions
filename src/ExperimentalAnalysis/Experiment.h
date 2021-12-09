//
// Created by louis on 08/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H

#include "../Solvers/HeuristicTreeDecompositionSolver/HeuristicTreeDecompositionSolver.h"
#include "../DataStructures/Colouring/BasicMHVEvaluator.h"

#include <map>

namespace ExperimentalAnalysis
{
    struct TestInstance
    {
        const std::string graphName{};
        const std::string treeDecompositionName{};
        const size_t nbColours{};
        const double percentColouredVertices{};
        const size_t nbColouringsPerGraph{};
        const size_t nbRepetitionsPerColouring{};
    };

    struct Experiment
    {
        const DataStructures::ColouringEvaluator* evaluator{};
        const std::map<std::string, Solvers::SolverBase*> baselines{};
        const std::map<std::string, Solvers::HeuristicTreeDecompositionSolver*> treeDecompositionSolvers{};
        const std::vector<TestInstance> testInstances{};
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H
