
#include "rng.h"
#include "IO/Reader.h"
#include "ExperimentalAnalysis/Experiment.h"
#include "ExperimentalAnalysis/experimentalAnalysis.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"
#include "DataStructures/Evaluator/PotentialHappyUncolouredMHVEvaluator.h"

#include "Solvers/MaximumHappyVertices/ExactAlgorithms/ExactTreeDecompositionMHVSolutionIterator.h"
#include "Solvers/MaximumHappyVertices/ExactAlgorithms/ExactTreeDecompositionMHV.h"
#include "Solvers/MaximumHappyVertices/ExactAlgorithms/ExactBruteForceMHV.h"
#include "ConstructingTreeDecompositions/TreeDecompositionSolverTimer.h"
#include "ConstructingTreeDecompositions/FlowCutter/FlowCutterAdapter.h"
#include "Solvers/SolversUtility/ColouringIterator.h"

#include <cstring>

int main(int argc, char** argv)
{
    std::string defaultRootDir = "../../";
    std::string defaultGraphFilesDir = defaultRootDir + "GraphFiles/";
    std::string defaultG6GraphFilesDir = defaultGraphFilesDir + "g6GraphFiles/";
    std::string defaultTreeDecompositionFilesDir = defaultRootDir + "TreeDecompositionFiles/";
    std::string defaultExperimentFilesDir = defaultRootDir + "ExperimentFiles/";
    std::string defaultResultFilesDir = defaultRootDir + "ResultFiles/";
    IO::Reader defaultReader{
            defaultGraphFilesDir,
            defaultG6GraphFilesDir,
            defaultTreeDecompositionFilesDir,
            defaultExperimentFilesDir,
            defaultResultFilesDir
    };
    if (argc == 1)
    {
        std::string solverFile{"initial_solvers.sol"};
        std::string experimentFile{"initial_experiment.exp"};
        ExperimentalAnalysis::Experiment experiment = defaultReader.readExperiment(solverFile, experimentFile);
        ExperimentalAnalysis::executeExperiment(defaultReader, experiment);

//        std::vector<DataStructures::ColourType> colouring;
//        DataStructures::Graph* graph = experiment.testInstances[0].graph;
//        for (auto const& [name, c] : experiment.testInstances[0].colourings)
//        {
//            colouring = c;
//            break;
//        }
//        graph->setInitialColours(colouring);

//        reader.readG6File("graph5c");
//        std::string name{"my_first_graph"};
//        std::string graphFile{name + ".gr"};
//        std::string treeFile{name + ".tw"};f
//        std::string niceTreeFile{name + "_nice.tw"};
//
//        TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//        timer.executeSolver(graphFile);
//        FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);
//        Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
    }
    else if (strcmp(argv[1], "stress-test") == 0)
    {
        DataStructures::Evaluator* problemEvaluator;
        Solvers::SolverBase* exactBruteForceSolver;
        Solvers::ExactTreeDecompositionSolverBase* exactTreeDecompositionSolver;
        if (strcmp(argv[2], "MHV") == 0)
        {
            problemEvaluator = new DataStructures::BasicMHVEvaluator{};
            exactBruteForceSolver = new MaximumHappyVertices::ExactBruteForceMHV{};
            exactTreeDecompositionSolver = new MaximumHappyVertices::ExactTreeDecompositionMHV{};
        }
        else
        {
            throw std::runtime_error("'" + std::string(argv[2]) + "' is not a valid problem!");
        }

        std::ifstream stressTests{defaultExperimentFilesDir + "stress_test.txt"};
        if (!stressTests)
            throw std::runtime_error("No stress-test file found at '" + defaultExperimentFilesDir + "stress_test.txt'!");

        std::string line;
        std::getline(stressTests, line);
        std::vector<std::string> tokens = IO::Reader::tokenize(line);

        int counter{0};
        int nbMistakes{0};
        while (stressTests)
        {
            counter++;

            if (tokens.size() != 4)
            {
                std::cerr << "The line '" << line << "' does not contain 4 arguments and is ignored.\n";
            }
            else
            {
                // TODO put bottom two lines in reader
//                FlowCutter::computeHeuristicTreeDecomposition(tokens[0], 1);
//                Jdrasil::computeNiceTreeDecomposition(tokens[0], tokens[0].substr(0, tokens[0].size()-3) + ".tw");

                DataStructures::Graph* graph = defaultReader.readGraph(tokens[0]);
                DataStructures::NiceTreeDecomposition niceTreeDecomposition = defaultReader.readNiceTreeDecomposition(tokens[1]);

                std::string colourString = "random(" + tokens[2] + "," + tokens[3] + ",1)";
                std::map<std::string, std::vector<DataStructures::ColourType>> colourVectors = IO::Reader::readColouringVector(colourString, graph);

                for (auto const& [name, colourVector] : colourVectors)
                {
                    graph->removeInitialColours();
                    graph->setInitialColours(colourVector);

                    exactBruteForceSolver->solve(graph);
                    int bruteForceEvaluation{problemEvaluator->evaluate(graph)};
                    graph->removeColours();

                    int tdEvaluation{exactTreeDecompositionSolver->solve(graph, &niceTreeDecomposition)};
                    graph->removeColours();

                    std::cout << "[brute force eval, exact td eval] = [" << bruteForceEvaluation << ", " << tdEvaluation << "]\n";
                    if (bruteForceEvaluation != tdEvaluation)
                    {
                        std::cerr << "[ERROR] - line: '" << line << "'\n";
                        nbMistakes++;
                    }
                }

                if (counter % 50 == 0)
                {
                    std::cout << "Done with stress test " << counter << "\n";
                }
            }

            std::getline(stressTests, line);
            tokens = IO::Reader::tokenize(line);
        }

        if (nbMistakes == 0)
        {
            std::cout << "All stress tests succeeded!\n";
        }
        else
        {
            std::cout << nbMistakes << " stress tests failed!\n";
        }
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
