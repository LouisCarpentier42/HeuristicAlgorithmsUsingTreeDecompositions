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
    void executeExperiment(IO::Reader& reader, Experiment& experiment);
//    void writeResults(size_t nbRepetitionsPerColouring,
//                      const std::string& solverName,
//                      const Solvers::SolverBase* solver,
//                      const DataStructures::ColouringEvaluator& evaluator);
    DataStructures::Colouring generatePartialColouring(DataStructures::Graph& graph, size_t nbColours, double percentColouredVertices);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENTALANALYSIS_H
