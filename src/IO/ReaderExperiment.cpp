//
// Created by louis on 09/12/2021.
//

#include "Reader.h"
#include "../Solvers/MaximumHappyVertices/ConstructionAlgorithms/GreedyMHV.h"
#include "../Solvers/MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/LeafNodeHandler/ConcreteLeafNodeHandlers.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/IntroduceNodeHandler/ConcreteIntroduceNodeHandlers.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/ForgetNodeHandler/ConcreteForgetNodeHandlers.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/JoinNodeHandler/ConcreteJoinNodeHandlers.h"
#include "../DataStructures/Colouring/AdvancedMHVEvaluator.h"

std::vector<std::string> splitParameters(std::string& str)
{
    std::stringstream strStream(str);
    std::string parametersString;
    std::vector<std::string> allParameters;
    while(std::getline(strStream, parametersString, '('))
        allParameters.push_back(parametersString);

    if (allParameters.size() == 1)
        return allParameters;

    allParameters.pop_back();
    parametersString.pop_back();

    std::string parameter;

    std::stringstream parametersStringStream(parametersString);
    while(std::getline(parametersStringStream, parameter, ','))
        allParameters.push_back(parameter);

    return allParameters;
}

const DataStructures::ColouringEvaluator* readEvaluator(std::string& str)
{
    std::vector<std::string> parameters = splitParameters(str);
    if (parameters[0] == "basicMHVEvaluator")
        return new DataStructures::BasicMHVEvaluator{};
    else if (parameters[0] == "advancedMHVEvaluator")
        return new DataStructures::AdvancedMHVEvaluator{
            IO::Reader::convertToInt(parameters[1]),
            IO::Reader::convertToInt(parameters[2]),
            IO::Reader::convertToInt(parameters[3])
        };
    throw std::runtime_error("Invalid evaluator identifier is given: " + str + "!");
}

Solvers::LeafNodeHandler* readLeafNodeHandler(std::string& str)
{
    if (str == "passive")
        return new Solvers::PassiveLeafNodeHandlers{};
    throw std::runtime_error("Invalid leaf node handler identifier is given: " + str + "!");
}

Solvers::IntroduceNodeHandler* readIntroduceNodeHandler(std::string& str)
{
    if (str == "bestColour")
        return new Solvers::BestColourIntroduceNodeHandler{};
    else if (str == "greedy")
        return new Solvers::GreedyIntroduceNodeHandler{};
    throw std::runtime_error("Invalid introduce node handler identifier is given: " + str + "!");
}

Solvers::ForgetNodeHandler* readForgetNodeHandler(std::string& str)
{
    if (str == "passive")
        return new Solvers::PassiveForgetNodeHandler{};
    throw std::runtime_error("Invalid forget node handler identifier is given: " + str + "!");
}

Solvers::JoinNodeHandler* readJoinNodeHandler(std::string& str)
{
    std::vector<std::string> parameters = splitParameters(str);
    if (parameters[0] == "staticOrder")
    {
        if (parameters[1] == "default")
            return new Solvers::StaticOrderJoinNodeHandler{Solvers::StaticOrderJoinNodeHandler::Order::defaultOrder};
        else if (parameters[1] == "gdf")
            return new Solvers::StaticOrderJoinNodeHandler{Solvers::StaticOrderJoinNodeHandler::Order::greatestDegreeFirst};
        else if (parameters[1] == "sdf")
            return new Solvers::StaticOrderJoinNodeHandler{Solvers::StaticOrderJoinNodeHandler::Order::smallestDegreeFirst};
        else if (parameters[1] == "random")
            return new Solvers::StaticOrderJoinNodeHandler{Solvers::StaticOrderJoinNodeHandler::Order::random};
    }
    else if (parameters[0] == "dynamicOrder")
    {
        return new Solvers::DynamicOrderJoinNodeHandler{};
    }

    throw std::runtime_error("Invalid join node handler identifier is given: " + str + "!");
}

ExperimentalAnalysis::Experiment IO::Reader::readExperiment(const std::string &filename) const
{
    std::ifstream file{experimentFilesDir + filename};
    if (!file)
    {
        throw std::runtime_error("Can't read graph in '" + filename + "' because the file can't be opened!");
    }

    DataStructures::ColouringEvaluator* evaluator{};
    std::map<std::string, Solvers::SolverBase*> baselines{};
    std::map<std::string, Solvers::HeuristicTreeDecompositionSolver*> treeDecompositionSolvers{};
    std::vector<ExperimentalAnalysis::TestInstance> testInstances{};
    while (file)
    {
        std::string line{};
        std::getline(file, line);
        std::vector<std::string> tokens = tokenize(line);
        if (tokens.empty() || tokens[0] == "c") continue;
        else if (tokens[0] == "problem")
        {
            if (evaluator)
                throw std::runtime_error("An experiment can only have 1 problem!");
            else if (tokens[1] == "MaximumHappyVertices")
                evaluator = new DataStructures::BasicMHVEvaluator{};
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
        else if (tokens[0] == "experiment")
        {
            testInstances.push_back(
                ExperimentalAnalysis::TestInstance{
                    tokens[1],
                    tokens[2],
                    static_cast<size_t>(convertToInt(tokens[3])),
                    std::stod(tokens[4]),
                    static_cast<size_t>(convertToInt(tokens[5])),
                    static_cast<size_t>(convertToInt(tokens[6])),
                }
            );
        }
        else
        {
            std::cout << "Invalid input format: ignoring '" << line << "'\n";
        }
    }

    if (!evaluator)
        throw std::runtime_error("An experiment must have a problem!");
    if (baselines.empty() && treeDecompositionSolvers.empty())
        throw std::runtime_error("An experiment must have at least one solver!");
    if (testInstances.empty())
        throw std::runtime_error("An experiment must have test instances!");

    return ExperimentalAnalysis::Experiment{evaluator, baselines, treeDecompositionSolvers, testInstances};
}


