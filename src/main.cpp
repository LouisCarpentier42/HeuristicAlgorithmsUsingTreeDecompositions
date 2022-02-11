
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
    // TODO include general seed variable somewhere
    if (argc == 1)
    {
        std::string defaultRootDir = "../../";
        std::string graphFilesDir = defaultRootDir + "GraphFiles/";
        std::string g6GraphFilesDir = graphFilesDir + "g6GraphFiles/";
        std::string treeDecompositionFilesDir = defaultRootDir + "TreeDecompositionFiles/";
        std::string experimentFilesDir = defaultRootDir + "ExperimentFiles/";
        std::string resultFilesDir = defaultRootDir + "ResultFiles/";
        IO::Reader reader{
            graphFilesDir,
            g6GraphFilesDir,
            treeDecompositionFilesDir,
            experimentFilesDir,
            resultFilesDir
        };

        std::string solverFile{"initial_solvers.sol"};
        std::string experimentFile{"initial_experiment.exp"};
        ExperimentalAnalysis::Experiment experiment = reader.readExperiment(solverFile, experimentFile);
        ExperimentalAnalysis::executeExperiment(reader, experiment);

        //    DataStructures::Graph* graph = experiment.testInstances[0].graph;
        //    std::vector<DataStructures::ColourType> colouring = experiment.testInstances[0].colourings[0];
        //    graph->setInitialColours(colouring);

        //    reader.readG6File("graph5c");
        //    std::string name{"my_first_graph"};
        //    std::string graphFile{name + ".gr"};
        //    std::string treeFile{name + ".tw"};f
        //    std::string niceTreeFile{name + "_nice.tw"};
        //
        //    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
        //    timer.executeSolver(graphFile);
        //    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);
        //    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
    }
    else
    {

    }

}
