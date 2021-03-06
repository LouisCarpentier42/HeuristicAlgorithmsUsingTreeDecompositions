//
// Created by louis on 09/12/2021.
//

#include "Reader.h"
#include "../Solvers/MaximumHappyVertices/ConstructionAlgorithms/GreedyMHV.h"
#include "../Solvers/MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h"
#include "../Solvers/MaximumHappyVertices/ExactAlgorithms/ExactTreeDecompositionMHV.h"
#include "../SolverV2/HeuristicMHVSolverV2.h"


std::shared_ptr<ExperimentalAnalysis::Experiment> IO::Reader::readExperiment(const std::string& solversFilename, const std::string& experimentsFilename) const
{
    std::ifstream solverFile{experimentFilesDir + solversFilename};
    if (!solverFile)
    {
        throw std::runtime_error("Can't read '" + experimentFilesDir + "/" + solversFilename + "' because the file can't be opened!");
    }

    std::ifstream experimentFile{experimentFilesDir + experimentsFilename};
    if (!experimentFile)
    {
        throw std::runtime_error("Can't read '" + experimentsFilename + "' because the file can't be opened!");
    }

    std::unique_ptr<Solvers::ExactTreeDecompositionSolverBase> exactTreeDecompositionSolver{};
    std::unique_ptr<DataStructures::Evaluator> evaluator{};
    std::map<std::string, std::shared_ptr<Solvers::SolverBase>> baselines{};
    std::map<std::string, std::shared_ptr<Solvers::HeuristicTreeDecompositionSolver>> treeDecompositionSolvers{};
    std::map<std::string, std::shared_ptr<SolverV2::HeuristicMHVSolverV2>> treeDecompositionSolversV2{};
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
                exactTreeDecompositionSolver = std::make_unique<MaximumHappyVertices::ExactTreeDecompositionMHV>();
                evaluator = std::make_unique<DataStructures::BasicMHVEvaluator>();
            }
        }
        else if (tokens[0] == "nbRepetitions")
        {
            nbRepetitionsPerInstance = static_cast<size_t>(convertToInt(tokens[1]));
        }
        else if (tokens[0] == "baseline")
        {
            if (tokens[1] == "greedyMHV")
                baselines["greedy-mhv"] = std::make_shared<MaximumHappyVertices::GreedyMHV>();
            else if (tokens[1] == "growthMHV")
                baselines["growth-mhv"] = std::make_shared<MaximumHappyVertices::GrowthMHV>();
            else
                throw std::runtime_error("Invalid baseline given " + tokens[1] + "!");
        }
        else if (tokens[0] == "heuristicTD")
        {
            auto leafNodeHandler = readLeafNodeHandler(tokens[4]);
            auto introduceNodeHandler = readIntroduceNodeHandler(tokens[5]);
            auto forgetNodeHandler = readForgetNodeHandler(tokens[6]);
            auto joinNodeHandler = readJoinNodeHandler(tokens[7]);
            treeDecompositionSolvers[tokens[1]] = std::make_shared<Solvers::HeuristicTreeDecompositionSolver>(
                static_cast<size_t>(convertToInt(tokens[2])),
                readEvaluator(tokens[3]),
                leafNodeHandler,
                introduceNodeHandler,
                forgetNodeHandler,
                joinNodeHandler
            );
        }
        else if (tokens[0] == "heuristicTD_V2")
        {
            std::string joinNodeRankingOrderString = tokens[7];
            SolverV2::HeuristicMHVSolverV2::JoinNodeRankingOrder joinNodeRankingOrder;
            if (joinNodeRankingOrderString == "largestRankingOut")
            {
                joinNodeRankingOrder = SolverV2::HeuristicMHVSolverV2::JoinNodeRankingOrder::largestRankingOut;
            }
            else if (joinNodeRankingOrderString == "smallestRankingOut")
            {
                joinNodeRankingOrder = SolverV2::HeuristicMHVSolverV2::JoinNodeRankingOrder::smallestRankingOut;
            }
            else if (joinNodeRankingOrderString == "randomRankingOut")
            {
                joinNodeRankingOrder = SolverV2::HeuristicMHVSolverV2::JoinNodeRankingOrder::randomRankingOut;
            }
            else
            {
                throw std::invalid_argument("Invalid order for rankings in join node: '" + joinNodeRankingOrderString + "'!");
            }

            std::string vertexWeightJoinBagString = tokens[8];
            SolverV2::HeuristicMHVSolverV2::VertexWeightJoinBag vertexWeightJoinBag;
            if (vertexWeightJoinBagString == "unitary")
            {
                vertexWeightJoinBag = SolverV2::HeuristicMHVSolverV2::VertexWeightJoinBag::unitary;
            }
            else if (vertexWeightJoinBagString == "nbColouredNeighboursOutsideBag")
            {
                vertexWeightJoinBag =  SolverV2::HeuristicMHVSolverV2::VertexWeightJoinBag::nbColouredNeighboursOutsideBag;
            }
            else if (vertexWeightJoinBagString == "hasColouredNeighbourOutsideBag")
            {
                vertexWeightJoinBag = SolverV2::HeuristicMHVSolverV2::VertexWeightJoinBag::hasColouredNeighbourOutsideBag;
            }
            else if (vertexWeightJoinBagString == "nbNeighboursOutsideBag")
            {
                vertexWeightJoinBag =  SolverV2::HeuristicMHVSolverV2::VertexWeightJoinBag::nbNeighboursOutsideBag;
            }
            else if (vertexWeightJoinBagString == "hasNeighboursOutsideBag")
            {
                vertexWeightJoinBag = SolverV2::HeuristicMHVSolverV2::VertexWeightJoinBag::hasNeighboursOutsideBag;
            }
            else if (vertexWeightJoinBagString == "nbNeighboursInBorder")
            {
                vertexWeightJoinBag =  SolverV2::HeuristicMHVSolverV2::VertexWeightJoinBag::nbNeighboursInBorder;
            }
            else if (vertexWeightJoinBagString == "hasNeighbourInBorder")
            {
                vertexWeightJoinBag = SolverV2::HeuristicMHVSolverV2::VertexWeightJoinBag::hasNeighbourInBorder;
            }
            else
            {
                throw std::invalid_argument("Invalid vertex weight for join node given: '" + joinNodeRankingOrderString + "'!");
            }

            std::string joinNodeCombineHeuristicString = tokens[9];
            SolverV2::HeuristicMHVSolverV2::JoinNodeCombineHeuristic joinNodeCombineHeuristic;
            if (joinNodeCombineHeuristicString == "copyBag")
            {
                joinNodeCombineHeuristic = SolverV2::HeuristicMHVSolverV2::JoinNodeCombineHeuristic::copyBag;
            }
            else if (joinNodeCombineHeuristicString == "merge")
            {
                joinNodeCombineHeuristic = SolverV2::HeuristicMHVSolverV2::JoinNodeCombineHeuristic::merge;
            }
            else
            {
                throw std::invalid_argument("Invalid join node combine heuristic given: '" + joinNodeRankingOrderString + "'!");
            }

            treeDecompositionSolversV2[tokens[1]] = std::make_shared<SolverV2::HeuristicMHVSolverV2>(
                    convertToInt(tokens[2]),
                    convertToInt(tokens[3]),
                    convertToInt(tokens[4]),
                    convertToInt(tokens[5]),
                    convertToInt(tokens[6]),
                    joinNodeRankingOrder,
                    vertexWeightJoinBag,
                    joinNodeCombineHeuristic
                );
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
            std::shared_ptr<DataStructures::Graph> graph = readGraph(tokens[1]);
            if (tokens.size() == 4)
            {
                testInstances.push_back(
                    ExperimentalAnalysis::TestInstance{
                            graph,
                            tokens[1],
                            tokens[2],
                            colourGraph(tokens[3], graph),
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
                                colourGraph(tokens[3], graph),
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
    if (baselines.empty() && treeDecompositionSolvers.empty() && treeDecompositionSolversV2.empty())
        throw std::runtime_error("An experiment must have at least one solver!");
    if (testInstances.empty())
        throw std::runtime_error("An experiment must have test instances!");

    std::string resultFile = resultFilesDir;
    resultFile.append(experimentsFilename.substr(0, experimentsFilename.size()-4));

    return std::make_shared<ExperimentalAnalysis::Experiment>(
        resultFile,
        std::move(exactTreeDecompositionSolver),
        std::move(evaluator),
        baselines,
        treeDecompositionSolvers,
        treeDecompositionSolversV2,
        testInstances,
        nbRepetitionsPerInstance
    );
}
