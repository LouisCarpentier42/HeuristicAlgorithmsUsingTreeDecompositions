//
// Created by louis on 08/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H

#include "../Solvers/SolverBase.h"
#include "../Solvers/ExactTreeDecompositionSolverBase.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/HeuristicTreeDecompositionSolver.h"
#include "../DataStructures/Evaluator/BasicMHVEvaluator.h"

#include <map>

namespace ExperimentalAnalysis
{
    struct TestInstance
    {
        DataStructures::Graph* graph;
        const std::string graphName;
        const std::string treeDecompositionName;
        const std::map<std::string, std::vector<DataStructures::ColourType>> colourings;
    };

    struct Experiment
    {
        const std::string resultFileName{};
        Solvers::ExactTreeDecompositionSolverBase* exactTreeDecompositionSolver{};
        const DataStructures::Evaluator* evaluator{};
        const std::map<std::string, Solvers::SolverBase*> baselines{};
        const std::map<std::string, Solvers::HeuristicTreeDecompositionSolver*> treeDecompositionSolvers{};
        const std::vector<TestInstance> testInstances{};
        const size_t nbRepetitionsPerInstance;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H
