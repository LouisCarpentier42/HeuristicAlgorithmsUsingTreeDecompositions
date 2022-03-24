//
// Created by louis on 08/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H

#include "../Solvers/SolverBase.h"
#include "../Solvers/ExactTreeDecompositionSolverBase.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/HeuristicTreeDecompositionSolver.h"
#include "../DataStructures/Evaluator/BasicMHVEvaluator.h"
#include "../SolverV2/HeuristicMHVSolverV2.h"

#include <map>

namespace ExperimentalAnalysis
{
    struct TestInstance
    {
        std::shared_ptr<DataStructures::Graph> graph;
        const std::string graphName;
        const std::string treeDecompositionName;
        const std::string colourGeneration;
        const bool executeExactTD;
        const bool compareExactTD;
    };

    struct Experiment
    {
        Experiment(
                std::string& resultFileName,
                std::unique_ptr<Solvers::ExactTreeDecompositionSolverBase> exactTreeDecompositionSolver,
                std::unique_ptr<DataStructures::Evaluator> evaluator,
                std::map<std::string, std::shared_ptr<Solvers::SolverBase>>& baselines,
                std::map<std::string, std::shared_ptr<Solvers::HeuristicTreeDecompositionSolver>>& treeDecompositionSolvers,
                std::map<std::string, std::shared_ptr<SolverV2::HeuristicMHVSolverV2>>& treeDecompositionSolversV2,
                std::vector<TestInstance>& testInstances,
                size_t nbRepetitionsPerInstance)
            : resultFileName(resultFileName),
              exactTreeDecompositionSolver(std::move(exactTreeDecompositionSolver)),
              evaluator(std::move(evaluator)),
              baselines(baselines),
              treeDecompositionSolvers(treeDecompositionSolvers),
              treeDecompositionSolversV2(treeDecompositionSolversV2),
              testInstances(testInstances),
              nbRepetitionsPerInstance(nbRepetitionsPerInstance)
        {}

        const std::string resultFileName{};
        std::unique_ptr<Solvers::ExactTreeDecompositionSolverBase> exactTreeDecompositionSolver{};
        std::unique_ptr<DataStructures::Evaluator> evaluator{};
        const std::map<std::string, std::shared_ptr<Solvers::SolverBase>> baselines{};
        const std::map<std::string, std::shared_ptr<Solvers::HeuristicTreeDecompositionSolver>> treeDecompositionSolvers{};
        const std::map<std::string, std::shared_ptr<SolverV2::HeuristicMHVSolverV2>> treeDecompositionSolversV2{};
        std::vector<TestInstance> testInstances{};
        const size_t nbRepetitionsPerInstance{};
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H
