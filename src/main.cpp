
#include "IO/Reader.h"
#include "ExperimentalAnalysis/Experiment.h"
#include "ExperimentalAnalysis/experimentalAnalysis.h"


int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    std::string graphFilesDir = "../GraphFiles/";
    std::string treeDecompositionFilesDir = "../TreeDecompositionFiles/";
    std::string experimentFilesDir = "../ExperimentFiles/";
    IO::Reader reader{
        graphFilesDir,
        treeDecompositionFilesDir,
        experimentFilesDir
    };

    std::string solverFile{"initial_solvers.sol"};
    std::string experimentFile{"initial_experiment.exp"};
    ExperimentalAnalysis::Experiment experiment = reader.readExperiment(solverFile, experimentFile);
    ExperimentalAnalysis::executeExperiment(reader, experiment);


//    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//    timer.executeSolver(graphFile);
//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);

//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeVeryNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);
}
