//
// Created by louis on 01/12/2021.
//

#include <chrono>
#include <random>
#include "experimentalAnalysis.h"


void ExperimentalAnalysis::executeExperiment(IO::Reader& reader, Experiment& experiment)
{
    for (const TestInstance& testInstance : experiment.testInstances)
    {
        DataStructures::Graph graph = reader.readGraph(testInstance.graphName);
        DataStructures::NiceTreeDecomposition niceTreeDecomposition = reader.readNiceTreeDecomposition(testInstance.treeDecompositionName);

        for (size_t colouringNb{0}; colouringNb < testInstance.nbColouringsPerGraph; colouringNb++)
        {
            DataStructures::Colouring colouring = generatePartialColouring(graph, testInstance.nbColours, testInstance.percentColouredVertices);

            // Test the baselines
            for (auto const& [name, baseline] : experiment.baselines)
            {
                std::cout << ">>> " << name << " <<<\n";

                auto start = std::chrono::high_resolution_clock::now();
                DataStructures::Colouring* solution = baseline->solve(&graph, &colouring);
                auto stop = std::chrono::high_resolution_clock::now();
                int evaluation{experiment.evaluator->evaluate(&graph, solution)};
                std::chrono::microseconds duration{std::chrono::duration_cast<std::chrono::microseconds>(stop - start)};

                std::cout << "Evaluation: " << evaluation << "\n";
                std::cout << "Time (µs):  " << duration.count() << "\n\n";
            }

            // Test the solvers
            for (auto const& [name, solver] : experiment.treeDecompositionSolvers)
            {
                std::cout << ">>> " << name << " <<<\n";
                std::chrono::microseconds duration{0};
                int evaluation{0};
                for (int repetition{0}; repetition < testInstance.nbRepetitionsPerColouring; repetition++)
                {
                    auto start = std::chrono::high_resolution_clock::now();
                    DataStructures::Colouring* solution = solver->solve(&graph, &colouring, &niceTreeDecomposition);
                    auto stop = std::chrono::high_resolution_clock::now();
                    duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                    evaluation += experiment.evaluator->evaluate(&graph, solution);
                }

                std::cout << "Evaluation: " << evaluation/testInstance.nbRepetitionsPerColouring << "\n";
                std::cout << "Time (µs):  " << duration.count()/testInstance.nbRepetitionsPerColouring << "\n\n";
            }
        }
    }
}



//    std::string graphFile{experiment.graphName + ".gr"};
//    std::string niceTreeFile{experiment.graphName + "_nice.tw"};
//
//    DataStructures::Graph graph = reader.readGraph(graphFile);
//    DataStructures::NiceTreeDecomposition niceTreeDecomposition = reader.readNiceTreeDecomposition(niceTreeFile);
//    DataStructures::BasicMHVEvaluator basicMhvEvaluator{};
//
//    for (int i{0}; i < experiment.nbColouringsPerGraph; i++)
//    {
//        DataStructures::Colouring colouring = generatePartialColouring(graph, experiment.nbColours, 0.01);

//        std::map<std::string, Solvers::SolverBase*> baselines{};
//        baselines["greedy_mhv"] = new MaximumHappyVertices::GreedyMHV{};
//        baselines["growth_mhv"] = new MaximumHappyVertices::GrowthMHV{};

        // The tree decomposition heuristics to test
//        std::map<std::string, Solvers::HeuristicTreeDecompositionSolver*> solvers{};
//        DataStructures::AdvancedMHVEvaluator evaluator{6, 2, -1};
//        solvers["my_basic_solver"] = new Solvers::HeuristicTreeDecompositionSolver{
//            experiment.nbColouringsToKeep,
//            &evaluator,
//            new Solvers::PassiveLeafNodeHandlers{},
//            new Solvers::ColourAllIntroduceNodeHandler{},
//            new Solvers::PassiveForgetNodeHandler{},
//            new Solvers::StaticOrderJoinNodeHandler{}
//        };
//        solvers["my_solver_best_colour_introduce"] = new Solvers::HeuristicTreeDecompositionSolver{
//            experiment.nbColouringsToKeep,
//            &evaluator,
//            new Solvers::PassiveLeafNodeHandlers{},
//            new Solvers::BestColourIntroduceNodeHandler{},
//            new Solvers::PassiveForgetNodeHandler{},
//            new Solvers::StaticOrderJoinNodeHandler{}
//        };



DataStructures::Colouring ExperimentalAnalysis::generatePartialColouring(DataStructures::Graph& graph, size_t nbColours, double percentColouredVertices)
{
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<DataStructures::ColourType> colourDistribution(1, nbColours);

    // Create a random shuffling of the vertices and colour them in this order
    std::vector<DataStructures::VertexType> allVertices(graph.getNbVertices());
    std::iota(allVertices.begin(), allVertices.end(), 0);
    std::shuffle(allVertices.begin(), allVertices.end(), rng);

    // Colour the first nbColours vertices in each colour before randomly colour the remaining vertices
    std::vector<DataStructures::ColourType> colourVector(graph.getNbVertices());
    for (int i{0}; i < nbColours; i++)
        colourVector[allVertices[i]] = i+1;
    for (size_t i{nbColours}; i < percentColouredVertices * graph.getNbVertices(); i++)
        colourVector[allVertices[i]] = colourDistribution(rng);

    return DataStructures::Colouring{colourVector};
}

