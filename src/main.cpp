
#include "IO/Reader.h"
#include "experimentalAnalysis.h"


int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    std::string graphFilesDir = "../GraphFiles/";
    std::string treeDecompositionFilesDir = "../TreeDecompositionFiles/";
    IO::Reader reader{graphFilesDir, treeDecompositionFilesDir};

    ExperimentalAnalysis::Experiment experiment{
        "ex001",
        3,
        8,
        5,
        2
    };

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
