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

        for (size_t colouringNb{0}; colouringNb < testInstance.nbColouringsPerGraph; colouringNb++)
        {
            DataStructures::Colouring colouring = generatePartialColouring(graph, testInstance.nbColours, testInstance.percentColouredVertices);
            std::cout << colouring << '\n';

            // Test the baselines
            for (auto const& [name, baseline] : experiment.baselines)
            {
                std::cout << ">>> " << name << " <<<\n";

                auto start = std::chrono::high_resolution_clock::now();
                DataStructures::Colouring* solution = baseline->solve(&graph, &colouring);
                auto stop = std::chrono::high_resolution_clock::now();
                int evaluation{experiment.evaluator->evaluate(&graph, solution)};
                std::chrono::microseconds duration{std::chrono::duration_cast<std::chrono::microseconds>(stop - start)};

                std::cout << *solution << '\n';
                std::cout << "Evaluation: " << evaluation << "\n";
                std::cout << "Time (µs):  " << duration.count() << "\n\n";
            }

            // Test the solvers
            if (!experiment.treeDecompositionSolvers.empty())
            {
                DataStructures::NiceTreeDecomposition niceTreeDecomposition = reader.readNiceTreeDecomposition(testInstance.treeDecompositionName);

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
}


DataStructures::Colouring ExperimentalAnalysis::generatePartialColouring(DataStructures::Graph& graph, size_t nbColours, double percentColouredVertices)
{
    static std::mt19937 rng{0};
//    static std::mt19937 rng{std::random_device{}()};
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

