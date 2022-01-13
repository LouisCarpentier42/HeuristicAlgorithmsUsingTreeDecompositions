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
        for (std::vector<DataStructures::ColourType> colouring : testInstance.colourings)
        {
            testInstance.graph->removeInitialColours();
            testInstance.graph->setInitialColours(colouring);

            // Test the baselines
            for (auto const& [name, baseline] : experiment.baselines)
            {
                testInstance.graph->removeColours();

                std::cout << ">>> " << name << " <<<\n";

                auto start = std::chrono::high_resolution_clock::now();
                baseline->solve(testInstance.graph);
                auto stop = std::chrono::high_resolution_clock::now();
                int evaluation{experiment.evaluator->evaluate(testInstance.graph)};
                std::chrono::microseconds duration{std::chrono::duration_cast<std::chrono::microseconds>(stop - start)};

                std::cout << testInstance.graph->getColourString() << "\n";
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
                        testInstance.graph->removeColours();
                        auto start = std::chrono::high_resolution_clock::now();
                        solver->solve(testInstance.graph, &niceTreeDecomposition);
                        auto stop = std::chrono::high_resolution_clock::now();
                        duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                        evaluation += experiment.evaluator->evaluate(testInstance.graph);
                    }
                    std::cout << testInstance.graph->getColourString() << "\n";
                    std::cout << "Evaluation: " << evaluation/testInstance.nbRepetitions << "\n";
                    std::cout << "Time (µs):  " << duration.count()/testInstance.nbRepetitions << "\n\n";
                }
            }
        }
    }
}
