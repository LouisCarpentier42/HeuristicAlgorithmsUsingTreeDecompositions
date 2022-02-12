
#include "rng.h"
#include "ExperimentalAnalysis/Experiment.h"
#include "ExperimentalAnalysis/experimentalAnalysis.h"
#include "IO/Reader.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"
#include "DataStructures/Evaluator/PotentialHappyUncolouredMHVEvaluator.h"

#include "Solvers/MaximumHappyVertices/ExactAlgorithms/ExactTreeDecompositionMHVSolutionIterator.h"
#include "ConstructingTreeDecompositions/TreeDecompositionSolverTimer.h"
#include "ConstructingTreeDecompositions/FlowCutter/FlowCutterAdapter.h"

#include <cstring>

int main(int argc, char** argv)
{
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
    else if (strcmp(argv[1], "heuristic-algorithm") == 0)
    {
        DataStructures::Evaluator* problemEvaluator;
        if (strcmp(argv[2], "MHV") == 0)
            problemEvaluator = new DataStructures::BasicMHVEvaluator{};
        else
            throw std::runtime_error("'" + std::string(argv[2]) + "' is not a valid problem!");

        IO::Reader reader{
            IO::Reader::getParameter(argc, argv, "--graphFilesDir", false),
            IO::Reader::getParameter(argc, argv, "--g6GraphFilesDir", false),
            IO::Reader::getParameter(argc, argv, "--treeDecompositionFilesDir", false),
            IO::Reader::getParameter(argc, argv, "--experimentFilesDir", false),
            IO::Reader::getParameter(argc, argv, "--resultFilesDir", false)
        };

        std::string seed = IO::Reader::getParameter(argc, argv, "--seed", false);
        if (!seed.empty())
            RNG::setRNG(std::strtoll(seed.c_str(), nullptr, 10));

        Solvers::HeuristicTreeDecompositionSolver solver{
            static_cast<size_t>(IO::Reader::convertToInt(IO::Reader::getParameter(argc, argv, "--nbSolutionsToKeep", true))),
            IO::Reader::readEvaluator(argc, argv),
            IO::Reader::readLeafNodeHandler(argc, argv),
            IO::Reader::readIntroduceNodeHandler(argc, argv),
            IO::Reader::readForgetNodeHandler(argc, argv),
            IO::Reader::readJoinNodeHandler(argc, argv)
        };

        DataStructures::Graph* graph = reader.readGraph(IO::Reader::getParameter(argc, argv, "--graphFile", true));
        graph->setInitialColours(IO::Reader::readColouringVector(argc, argv, graph));
        DataStructures::NiceTreeDecomposition treeDecomposition = reader.readNiceTreeDecomposition(IO::Reader::getParameter(argc, argv, "--treeDecompositionFile", true));

        solver.solve(graph, &treeDecomposition);

        std::cout << "Evaluation for '" << argv[2] << "': " << problemEvaluator->evaluate(graph) << "." << std::endl;
    }
    else
    {
        throw std::runtime_error("Invalid argument '" + std::string{argv[1]} + "'!");
    }
}
