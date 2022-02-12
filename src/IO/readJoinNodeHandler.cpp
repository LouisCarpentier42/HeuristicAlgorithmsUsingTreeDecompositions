//
// Created by louis on 12/02/2022.
//

#include "Reader.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/JoinNodeHandler/ConcreteJoinNodeHandlers.h"

Solvers::JoinNodeHandler* createJoinNodeHandler(std::vector<std::string> parameters)
{
    Solvers::EvaluationMerger* merger = IO::Reader::getEvaluationMerger(parameters[1]);

    if (parameters[0] == "staticOrder")
    {
        if (parameters[2] == "default")
            return new Solvers::StaticOrderJoinNodeHandler{merger, Solvers::StaticOrderJoinNodeHandler::Order::defaultOrder};
        else if (parameters[2] == "gdf")
            return new Solvers::StaticOrderJoinNodeHandler{merger, Solvers::StaticOrderJoinNodeHandler::Order::greatestDegreeFirst};
        else if (parameters[2] == "sdf")
            return new Solvers::StaticOrderJoinNodeHandler{merger, Solvers::StaticOrderJoinNodeHandler::Order::smallestDegreeFirst};
        else if (parameters[2] == "random")
            return new Solvers::StaticOrderJoinNodeHandler{merger, Solvers::StaticOrderJoinNodeHandler::Order::random};
    }
    else if (parameters[0] == "dynamicOrder")
    {
        if (parameters[2] == "mostColouredNeighbours")
            return new Solvers::DynamicOrderJoinNodeHandler{merger, Solvers::DynamicOrderJoinNodeHandler::Order::mostColouredNeighboursFirst};
        else if (parameters[2] == "fewestColouredNeighboursFirst")
            return new Solvers::DynamicOrderJoinNodeHandler{merger, Solvers::DynamicOrderJoinNodeHandler::Order::fewestColouredNeighboursFirst};
        else if (parameters[2] == "mostPotentialHappyNeighbours")
            return new Solvers::DynamicOrderJoinNodeHandler{merger, Solvers::DynamicOrderJoinNodeHandler::Order::mostPotentialHappyNeighbours};
        else if (parameters[2] == "mostPercentPotentialHappyNeighbours")
            return new Solvers::DynamicOrderJoinNodeHandler{merger, Solvers::DynamicOrderJoinNodeHandler::Order::mostPercentPotentialHappyNeighbours};
    }
    else if (parameters[0] == "greedyColourBag")
    {
        return new Solvers::GreedyColourBagJoinNodeHandler{merger};
    }
    else if (parameters[0] == "growthColourBag")
    {
        return new Solvers::GrowthColourBagJoinNodeHandler{merger};
    }
    else if (parameters[0] == "useChildColours")
    {
        return new Solvers::UseChildColoursJoinNodeHandler{merger};
    }
    throw std::runtime_error("Invalid join node handler identifier is given: " + parameters[0] + "!");
}

Solvers::JoinNodeHandler* IO::Reader::readJoinNodeHandler(const std::string& str)
{
    return createJoinNodeHandler(splitParameters(str));
}

Solvers::JoinNodeHandler* IO::Reader::readJoinNodeHandler(int argc, char** argv)
{
    std::string joinNodeHandler = getParameter(argc, argv, "--joinNodeHandler", true);
    std::vector<std::string> parameters;
    parameters.push_back(joinNodeHandler);
    parameters.push_back(getParameter(argc, argv, "--evaluationMerger", true));
    //    if (joinNodeHandler == "greedyColourBag") {}
    //    if (joinNodeHandler == "growthColourBag") {}
    //    if (joinNodeHandler == "useChildColours") {}
    if (joinNodeHandler == "dynamicOrder")
        parameters.push_back(getParameter(argc, argv, "--dynamicOrder", true));
    if (joinNodeHandler == "staticOrder")
        parameters.push_back(getParameter(argc, argv, "--staticOrder", true));
    return createJoinNodeHandler(parameters);
}

Solvers::EvaluationMerger* IO::Reader::getEvaluationMerger(const std::string& str)
{
    if (str == "avg")
        return new Solvers::AverageEvaluationMerger{};
    else if (str == "max")
        return new Solvers::MaximumEvaluationMerger{};
    else if (str == "min")
        return new Solvers::MinimumEvaluationMerger{};

    throw std::runtime_error("Invalid evaluation merger identifier is given: " + str + "!");
}
