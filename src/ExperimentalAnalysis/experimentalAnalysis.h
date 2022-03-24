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
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENTALANALYSIS_H
