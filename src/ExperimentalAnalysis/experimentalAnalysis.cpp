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
        for (DataStructures::Colouring* colouring : testInstance.colourings)
        {
            // Test the baselines
            for (auto const& [name, baseline] : experiment.baselines)
            {
                std::cout << ">>> " << name << " <<<\n";

                auto start = std::chrono::high_resolution_clock::now();
                DataStructures::Colouring* solution = baseline->solve(testInstance.graph, colouring);
                auto stop = std::chrono::high_resolution_clock::now();
                int evaluation{experiment.evaluator->evaluate(testInstance.graph, solution)};
                std::chrono::microseconds duration{std::chrono::duration_cast<std::chrono::microseconds>(stop - start)};

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
                    for (int repetition{0}; repetition < testInstance.nbRepetitions; repetition++)
                    {
                        auto start = std::chrono::high_resolution_clock::now();
                        DataStructures::Colouring* solution = solver->solve(testInstance.graph, colouring, &niceTreeDecomposition);
                        auto stop = std::chrono::high_resolution_clock::now();
                        duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                        evaluation += experiment.evaluator->evaluate(testInstance.graph, solution);
                    }

                    std::cout << "Evaluation: " << evaluation/testInstance.nbRepetitions << "\n";
                    std::cout << "Time (µs):  " << duration.count()/testInstance.nbRepetitions << "\n\n";
                }
            }
        }
    }
}


