//
// Created by louis on 01/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENTALANALYSIS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENTALANALYSIS_H

#include <string>
#include <vector>
#include <map>
#include "../IO/Reader.h"
#include "../Solvers/SolverBase.h"
#include "Experiment.h"

namespace ExperimentalAnalysis
{
    void executeExperiment(IO::Reader& reader, std::shared_ptr<Experiment>& experiment);
    void executeExperimentV2(IO::Reader& reader, std::shared_ptr<Experiment>& experiment);

    void executeSolverAndWriteResultsToFile(
            std::ofstream& file,
            const std::shared_ptr<SolverV2::HeuristicMHVSolverV2>& solver,
            const std::string& solverName,
            const std::unique_ptr<DataStructures::Evaluator>& evaluator,
            std::shared_ptr<DataStructures::Graph>& graph,
            const std::string& graphName,
            std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition,
            const std::string& treeDecompositionName);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENTALANALYSIS_H
