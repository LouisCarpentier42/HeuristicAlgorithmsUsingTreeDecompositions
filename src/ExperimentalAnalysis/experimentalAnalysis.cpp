//
// Created by louis on 01/12/2021.
//

#include <chrono>
#include <random>
#include "experimentalAnalysis.h"

void ExperimentalAnalysis::executeExperiment(IO::Reader& reader, Experiment& experiment)
{
    std::ofstream resultFile;
    resultFile.open(experiment.resultFileName + ".csv");
    resultFile << "Solver name,graph name,tree decomposition name,initial colouring name,";
    for (int i{0}; i < experiment.nbRepetitionsPerInstance; i++)
        resultFile << "evaluation run " << (i+1) << ",time (µs) run " << (i+1) << ",";
    resultFile << "mean evaluation,mean time(µs)\n";

    for (const TestInstance& testInstance : experiment.testInstances)
    {
        for (auto const& [colouringName, colouring] : testInstance.colourings)
        {
            testInstance.graph->removeInitialColours();
            testInstance.graph->setInitialColours(colouring);

            // Test the baselines
            for (auto const& [name, baseline] : experiment.baselines)
            {
                resultFile << name << "," << testInstance.graphName << "," << testInstance.treeDecompositionName << "," << colouringName << ",";
                std::chrono::microseconds duration{0};
                int evaluation{0};
                for (int repetition{0}; repetition < experiment.nbRepetitionsPerInstance; repetition++)
                {
                    testInstance.graph->removeColours();
                    auto start = std::chrono::high_resolution_clock::now();
                    baseline->solve(testInstance.graph);
                    auto stop = std::chrono::high_resolution_clock::now();
                    int newEvaluation{experiment.evaluator->evaluate(testInstance.graph)};
                    evaluation += newEvaluation;
                    duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                    resultFile << newEvaluation << "," << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << ",";
                }
//                std::cout << testInstance.graph->getColourString() << "\n";
//                std::cout << "Evaluation: " << evaluation/experiment.nbRepetitionsPerInstance << "\n";
//                std::cout << "Time (µs):  " << duration.count()/experiment.nbRepetitionsPerInstance << "\n\n";
                resultFile << evaluation/experiment.nbRepetitionsPerInstance << "," << duration.count()/experiment.nbRepetitionsPerInstance << "\n";
            }

            // Test the solvers
            if (!experiment.treeDecompositionSolvers.empty())
            {
                DataStructures::NiceTreeDecomposition niceTreeDecomposition = reader.readNiceTreeDecomposition(testInstance.treeDecompositionName);

                for (auto const& [name, solver] : experiment.treeDecompositionSolvers)
                {
                    resultFile << name << "," << testInstance.graphName << "," << testInstance.treeDecompositionName << "," << colouringName << ",";
                    std::chrono::microseconds duration{0};
                    int evaluation{0};
                    for (int repetition{0}; repetition < experiment.nbRepetitionsPerInstance; repetition++)
                    {
                        testInstance.graph->removeColours();
                        auto start = std::chrono::high_resolution_clock::now();
                        solver->solve(testInstance.graph, &niceTreeDecomposition);
                        auto stop = std::chrono::high_resolution_clock::now();
                        int newEvaluation{experiment.evaluator->evaluate(testInstance.graph)};
                        evaluation += newEvaluation;
                        duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                        resultFile << newEvaluation << "," << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << ",";
                    }
                    resultFile << evaluation/experiment.nbRepetitionsPerInstance << "," << duration.count()/experiment.nbRepetitionsPerInstance << "\n";
                }
            }
        }
    }
    resultFile.close();
}
