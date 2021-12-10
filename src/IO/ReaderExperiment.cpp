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
#include "../DataStructures/ColouringEvaluator/PotentialHappyColouredMHVEvaluator.h"
#include "../DataStructures/ColouringEvaluator/PotentialHappyUncolouredMHVEvaluator.h"

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
    else if (parameters[0] == "colouredMHVEvaluator")
        return new DataStructures::PotentialHappyColouredMHVEvaluator{
            IO::Reader::convertToInt(parameters[1]),
            IO::Reader::convertToInt(parameters[2]),
            IO::Reader::convertToInt(parameters[3])
        };
    else if (parameters[0] == "uncolouredMHVEvaluator")
        return new DataStructures::PotentialHappyUncolouredMHVEvaluator{
            IO::Reader::convertToInt(parameters[1]),
            IO::Reader::convertToInt(parameters[2]),
            IO::Reader::convertToInt(parameters[3]),
            IO::Reader::convertToInt(parameters[4]),
            IO::Reader::convertToInt(parameters[5]),
            IO::Reader::convertToInt(parameters[6])
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
    else if (parameters[0] == "greedyColourBag")
    {
        return new Solvers::GreedyColourBagJoinNodeHandler{};
    }

    throw std::runtime_error("Invalid join node handler identifier is given: " + str + "!");
}

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

    DataStructures::ColouringEvaluator* evaluator{};
    std::map<std::string, Solvers::SolverBase*> baselines{};
    std::map<std::string, Solvers::HeuristicTreeDecompositionSolver*> treeDecompositionSolvers{};
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
            std::cout << "Invalid input format: ignoring line '" << line << "'\n";
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


