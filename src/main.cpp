
#include "ExperimentalAnalysis/Experiment.h"
#include "ExperimentalAnalysis/experimentalAnalysis.h"
#include "IO/Reader.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"
#include "DataStructures/Evaluator/PotentialHappyUncolouredMHVEvaluator.h"

#include "Solvers/MaximumHappyVertices/ExactAlgorithms/ExactTreeDecompositionSolutionIterator.h"

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

//    DataStructures::Graph* graph = experiment.testInstances[0].graph;
//    std::vector<DataStructures::ColourType> colouring = experiment.testInstances[0].colourings[0];
//    graph->setInitialColours(colouring);

//    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//    timer.executeSolver(graphFile);
//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);

//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeVeryNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);
}
