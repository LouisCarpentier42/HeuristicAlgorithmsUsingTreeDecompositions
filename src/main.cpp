
#include "SolverV2/HeuristicMHVSolverV2.h"

#include "rng.h"
#include "IO/Reader.h"
#include "ExperimentalAnalysis/Experiment.h"
#include "ExperimentalAnalysis/experimentalAnalysis.h"
#include "DataStructures/Evaluator/GrowthMHVEvaluator.h"

#include "Solvers/MaximumHappyVertices/ExactAlgorithms/ExactTreeDecompositionMHVSolutionIterator.h"
#include "Solvers/MaximumHappyVertices/ExactAlgorithms/ExactTreeDecompositionMHV.h"
#include "Solvers/MaximumHappyVertices/ExactAlgorithms/ExactBruteForceMHV.h"
#include "ConstructingTreeDecompositions/Constructor.h"

#include <cstring>
#include <chrono>

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./HeuristicAlgorithmsUsingTreeDecompositions
// valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./HeuristicAlgorithmsUsingTreeDecompositions
int main(int argc, char** argv)
{
    RNG::setRNG(1);
//    RNG::setRNG(std::random_device{}());
    std::string defaultRootDir = IO::Reader::getParameter(argc, argv, "--rootDir", false);
    if (defaultRootDir.empty())
        defaultRootDir = "../../";
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
    std::string defaultFlowCutterDir = defaultRootDir + "src/ConstructingTreeDecompositions/FlowCutter/flow-cutter-pace17/";
    std::string defaultJdrasilDir = defaultRootDir + "src/ConstructingTreeDecompositions/Jdrasil/";
    ConstructTreeDecompositions::Constructor defaultConstructor{
        defaultReader,
        defaultFlowCutterDir,
        defaultJdrasilDir
    };

    if (argc == 1)
    {

        std::set<int> indices{1,2,3};
        auto comparator =
                [indices]
                (auto& v1, auto& v2)
                {
                    for (int index : indices)
                    {
                        if (v1[index] != v2[index])
                            return v1[index] < v2[index];
                    }
                    return false;
                };
        std::set<std::vector<int>, decltype(comparator)> s(comparator);
//        std::set<std::vector<int>> s{};

        s.insert(std::vector<int>{1,2,3});
        s.insert(std::vector<int>{2,3,4});
        s.insert(std::vector<int>{1,3,3});


        int counter{1};
        for (const std::vector<int>& vector : s)
        {
            std::cout << "vector " << counter++ << ": [";
            for (int i : vector) std::cout << i << ", ";
            std::cout << "]\n";
        }





////        std::string solverFile{"greedy_vs_growth.sol"};
////        std::string experimentFile{"lewis_random_greedy_vs_growth.exp"};
//
//        std::string solverFile{"initial_solvers.sol"};
////        std::string experimentFile{"grid_graphs.exp"};
//        std::string experimentFile{"small_random_graphs.exp"};
//
////        std::string solverFile{"greedy_vs_growth.sol"};
////        std::string experimentFile{"initial_experiment.exp"};
////        std::string experimentFile{"small_random_graphs.exp"};
//
//        std::shared_ptr<ExperimentalAnalysis::Experiment> experiment = defaultReader.readExperiment(solverFile, experimentFile);
//        ExperimentalAnalysis::executeExperimentV2(defaultReader, experiment);
    }
    else if (strcmp(argv[1], "v2") == 0)
    {
        std::string solverFile{"greedy_vs_growth.sol"};
//        std::string experimentFile{"initial_experiment.exp"};
        std::string experimentFile{"small_random_graphs.exp"};
        std::shared_ptr<ExperimentalAnalysis::Experiment> experiment = defaultReader.readExperiment(solverFile, experimentFile);

        for (ExperimentalAnalysis::TestInstance& testInstance : experiment->testInstances)
        {
            std::cout << " --- Graph: " << testInstance.graphName << " ---\n";
            // Test the baselines
            for (auto const& [name, baseline] : experiment->baselines)
            {
                std::cout << "Baseline: " << name << "\n";

                testInstance.graph->removeColours();
                auto start = std::chrono::high_resolution_clock::now();
                baseline->solve(testInstance.graph);
                auto stop = std::chrono::high_resolution_clock::now();
                int evaluation{experiment->evaluator->evaluate(testInstance.graph)};

                std::cout  << "[evaluation,time] = [" << evaluation << "," << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "]\n";
                std::cout  << "\n";
            }

            int nbSolutionsToKeep;
            if (argc == 3)
                nbSolutionsToKeep = IO::Reader::convertToInt(argv[2]);
            else
                nbSolutionsToKeep = 8;
//            MaximumHappyVertices::ExactTreeDecompositionMHV solverV2{};
            SolverV2::HeuristicMHVSolverV2 solverV2{nbSolutionsToKeep, 2, 1, 0};
            std::cout << "Solver V2 with " << nbSolutionsToKeep << " entries to keep\n";

            std::shared_ptr<DataStructures::NiceTreeDecomposition> td = defaultReader.readNiceTreeDecomposition(testInstance.treeDecompositionName);

            testInstance.graph->removeColours();
            auto start = std::chrono::high_resolution_clock::now();
            solverV2.solve(testInstance.graph, td);
            auto stop = std::chrono::high_resolution_clock::now();
            int evaluation{experiment->evaluator->evaluate(testInstance.graph)};

            std::cout  << "[evaluation,time] = [" << evaluation << "," << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "]\n";
            std::cout  << "\n";

            std::cout << "--------------------------------------------\n";
        }
    }
    else if (strcmp(argv[1], "construct") == 0 || strcmp(argv[1], "construct-nice") == 0)
    {
        auto flowCutter = ConstructTreeDecompositions::ConstructionAlgorithm::FlowCutter;
        std::string graphFile = IO::Reader::getParameter(argc, argv, "--graph", true);
        double time = std::stod(IO::Reader::getParameter(argc, argv, "--time", true));
        if (strcmp(argv[1], "construct") == 0)
            std::string file = defaultConstructor.construct(flowCutter, graphFile, time);
        else
            std::string file = defaultConstructor.constructNice(flowCutter, graphFile, time);
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
                if (!IO::Reader::pathExists(defaultReader.treeDecompositionFilesDir + tokens[1]))
                {
                    tokens[1] = defaultConstructor.constructNice(
                                    ConstructTreeDecompositions::ConstructionAlgorithm::FlowCutter,
                                    tokens[0],
                                    0.1);
                }

                std::shared_ptr<DataStructures::Graph> graph = defaultReader.readGraph(tokens[0]);
                std::shared_ptr<DataStructures::NiceTreeDecomposition> niceTreeDecomposition = defaultReader.readNiceTreeDecomposition(tokens[1]);
                std::string colourType = IO::Reader::colourGraph("random(" + tokens[2] + "," + tokens[3] + ")", graph);

                exactBruteForceSolver->solve(graph);
                int bruteForceEvaluation{problemEvaluator->evaluate(graph)};
                graph->removeColours();

                SolverV2::HeuristicMHVSolverV2 solverV2{1024, 1, 0, 0}; // TODO set back to exact algo
                solverV2.solve(graph, niceTreeDecomposition);
                int tdEvaluation = problemEvaluator->evaluate(graph);
//                int tdEvaluation{exactTreeDecompositionSolver->solve(graph, niceTreeDecomposition)};
                int tdColouringEvaluation{problemEvaluator->evaluate(graph)};
                graph->removeColours();

                std::cout << counter << ": [brute force eval, exact td eval] = [" << bruteForceEvaluation << ", " << tdEvaluation << "]\n";
                if (bruteForceEvaluation != tdEvaluation)
                {
                    std::cout << "[ERROR]: brute force and td have different evaluation: " << tokens[0] << " " << tokens[1] << "\n";
                    nbMistakes++;
                }

                if (tdColouringEvaluation != tdEvaluation)
                {
                    std::cout << "[ERROR] evaluation graph differs from evaluation td algorithm: [" << tdEvaluation << ", " << tdColouringEvaluation << "]\n";
                    nbMistakes++;
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

        auto leafNodeHandler = IO::Reader::readLeafNodeHandler(argc, argv);
        auto introduceNodeHandler = IO::Reader::readIntroduceNodeHandler(argc, argv);
        auto forgetNodeHandler = IO::Reader::readForgetNodeHandler(argc, argv);
        auto joinNodeHandler = IO::Reader::readJoinNodeHandler(argc, argv);
        Solvers::HeuristicTreeDecompositionSolver solver{
            static_cast<size_t>(IO::Reader::convertToInt(IO::Reader::getParameter(argc, argv, "--nbSolutionsToKeep", true))),
            IO::Reader::readEvaluator(argc, argv),
            leafNodeHandler,
            introduceNodeHandler,
            forgetNodeHandler,
            joinNodeHandler
        };

        std::shared_ptr<DataStructures::Graph> graph = reader.readGraph(IO::Reader::getParameter(argc, argv, "--graphFile", true));
        std::string colourType = IO::Reader::colourGraph(argc, argv, graph);
        std::shared_ptr<DataStructures::NiceTreeDecomposition> treeDecomposition = reader.readNiceTreeDecomposition(IO::Reader::getParameter(argc, argv, "--treeDecompositionFile", true));

        solver.solve(graph, treeDecomposition);

        std::cout << "Evaluation for '" << argv[2] << "': " << problemEvaluator->evaluate(graph) << "." << std::endl;
    }
    else
    {
        throw std::runtime_error("Invalid argument '" + std::string{argv[1]} + "'!");
    }
}
