//
// Created by louis on 09/12/2021.
//

#include "Reader.h"
#include "../Solvers/MaximumHappyVertices/ConstructionAlgorithms/GreedyMHV.h"
#include "../Solvers/MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h"
#include "../Solvers/MaximumHappyVertices/ExactAlgorithms/ExactTreeDecompositionMHV.h"

#include <random>


ExperimentalAnalysis::Experiment IO::Reader::readExperiment(const std::string& solversFilename, const std::string& experimentsFilename) const
{
    std::ifstream solverFile{experimentFilesDir + solversFilename};
    if (!solverFile)
    {
        throw std::runtime_error("Can't read '" + solversFilename + "' because the file can't be opened!");
    }

    std::ifstream experimentFile{experimentFilesDir + experimentsFilename};
    if (!experimentFile)
    {
        throw std::runtime_error("Can't read '" + experimentsFilename + "' because the file can't be opened!");
    }

    Solvers::ExactTreeDecompositionSolverBase* exactTreeDecompositionSolver{};
    DataStructures::Evaluator* evaluator{};
    std::map<std::string, Solvers::SolverBase*> baselines{};
    std::map<std::string, Solvers::HeuristicTreeDecompositionSolver*> treeDecompositionSolvers{};
    size_t nbRepetitionsPerInstance{1};
    while (solverFile)
    {
        std::string line{};
        std::getline(solverFile, line);
        std::vector<std::string> tokens = tokenize(line);
        if (tokens.empty() || tokens[0] == "c") continue;
        else if (tokens[0] == "problem")
        {
            if (evaluator)
                throw std::runtime_error("An experiment can only have 1 problem!");
            else if (tokens[1] == "MaximumHappyVertices")
            {
                exactTreeDecompositionSolver = new MaximumHappyVertices::ExactTreeDecompositionMHV{};
                evaluator = new DataStructures::BasicMHVEvaluator{};
            }
        }
        else if (tokens[0] == "nbRepetitions")
        {
            nbRepetitionsPerInstance = static_cast<size_t>(convertToInt(tokens[1]));
        }
        else if (tokens[0] == "baseline")
        {
            if (tokens[1] == "greedyMHV")
                baselines["greedy-mhv"] = new MaximumHappyVertices::GreedyMHV{};
            else if (tokens[1] == "growthMHV")
                baselines["growth-mhv"] = new MaximumHappyVertices::GrowthMHV{};
            else
                throw std::runtime_error("Invalid baseline given " + tokens[1] + "!");
        }
        else if (tokens[0] == "heuristicTD")
        {
            treeDecompositionSolvers[tokens[1]] = new Solvers::HeuristicTreeDecompositionSolver{
                static_cast<size_t>(convertToInt(tokens[2])),
                readEvaluator(tokens[3]),
                readLeafNodeHandler(tokens[4]),
                readIntroduceNodeHandler(tokens[5]),
                readForgetNodeHandler(tokens[6]),
                readJoinNodeHandler(tokens[7]),
            };
        }
        else
        {
            std::cout << "Invalid input format: ignoring line '" << line << "'\n";
        }
    }

    std::vector<ExperimentalAnalysis::TestInstance> testInstances{};
    while (experimentFile)
    {
        std::string line{};
        std::getline(experimentFile, line);
        std::vector<std::string> tokens = tokenize(line);
        if (tokens.empty() || tokens[0] == "c") continue;
        else if (tokens[0] == "experiment")
        {
            DataStructures::Graph* graph = readGraph(tokens[1]);
            if (tokens.size() == 4)
            {
                testInstances.push_back(
                    ExperimentalAnalysis::TestInstance{
                        graph,
                        tokens[1],
                        tokens[2],
                        readColouringString(tokens[3], graph),
                        false,
                        false
                    }
                );
            }
            else
            {
                std::vector<std::string> parameters = splitParameters(tokens[4]);
                if (parameters[0] == "exactTD")
                {
                    testInstances.push_back(
                        ExperimentalAnalysis::TestInstance{
                            graph,
                            tokens[1],
                            tokens[2],
                            readColouringString(tokens[3], graph),
                            parameters[1] == "true",
                            parameters[2] == "true"
                        }
                    );
                }
                else
                {
                    std::cout << "Invalid extra parameters for experiment: ignoring '" << tokens[4] << "'\n";
                }
            }
        }
        else
        {
            std::cout << "Invalid input format: ignoring line '" << line << "'\n";
        }
    }

    if (!evaluator)
        throw std::runtime_error("An experiment must have a problem!");
    if (baselines.empty() && treeDecompositionSolvers.empty())
        throw std::runtime_error("An experiment must have at least one solver!");
    if (testInstances.empty())
        throw std::runtime_error("An experiment must have test instances!");

    std::string resultFile = resultFilesDir;
    resultFile.append(experimentsFilename.substr(0, experimentsFilename.size()-4));

    return ExperimentalAnalysis::Experiment{
        resultFile,
        exactTreeDecompositionSolver,
        evaluator,
        baselines,
        treeDecompositionSolvers,
        testInstances,
        nbRepetitionsPerInstance
    };
}


