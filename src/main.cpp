
#include "ExperimentalAnalysis/Experiment.h"
#include "ExperimentalAnalysis/experimentalAnalysis.h"
#include "IO/Reader.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"
#include "DataStructures/Evaluator/PotentialHappyUncolouredMHVEvaluator.h"

#include "Solvers/MaximumHappyVertices/ExactAlgorithms/ExactTreeDecompositionMHVSolutionIterator.h"
#include "ConstructingTreeDecompositions/TreeDecompositionSolverTimer.h"
#include "ConstructingTreeDecompositions/FlowCutter/FlowCutterAdapter.h"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    std::string graphFilesDir = "../GraphFiles/";
    std::string g6GraphFilesDir = graphFilesDir + "g6GraphFiles/";
    std::string treeDecompositionFilesDir = "../TreeDecompositionFiles/";
    std::string experimentFilesDir = "../ExperimentFiles/";
    std::string resultFilesDir = "../ResultFiles/";
    IO::Reader reader{
        graphFilesDir,
        g6GraphFilesDir,
        treeDecompositionFilesDir,
        experimentFilesDir,
        resultFilesDir
    };

//    reader.readG6File("graph5c");

    std::string solverFile{"initial_solvers.sol"};
    std::string experimentFile{"initial_experiment.exp"};
    ExperimentalAnalysis::Experiment experiment = reader.readExperiment(solverFile, experimentFile);
    ExperimentalAnalysis::executeExperiment(reader, experiment);

//    DataStructures::Graph* graph = experiment.testInstances[0].graph;
//    std::vector<DataStructures::ColourType> colouring = experiment.testInstances[0].colourings[0];
//    graph->setInitialColours(colouring);

//    std::string name{"my_first_graph"};
//    std::string graphFile{name + ".gr"};
//    std::string treeFile{name + ".tw"};
//    std::string niceTreeFile{name + "_nice.tw"};
//
//    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//    timer.executeSolver(graphFile);
//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);
//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
}
