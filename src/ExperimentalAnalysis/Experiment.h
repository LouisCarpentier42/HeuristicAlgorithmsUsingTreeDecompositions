//
// Created by louis on 08/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H

#include "../Solvers/HeuristicTreeDecompositionSolver/HeuristicTreeDecompositionSolver.h"
#include "../DataStructures/ColouringEvaluator/BasicMHVEvaluator.h"

#include <map>

namespace ExperimentalAnalysis
{
    struct TestInstance
    {
        const DataStructures::Graph* graph;
        const std::string treeDecompositionName;
        const std::vector<DataStructures::Colouring*> colourings;
        const size_t nbRepetitions;
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
