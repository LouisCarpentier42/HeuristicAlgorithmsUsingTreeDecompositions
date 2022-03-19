//
// Created by louis on 12/02/2022.
//

#include "Reader.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/JoinNodeHandler/ConcreteJoinNodeHandlers.h"

std::shared_ptr<Solvers::JoinNodeHandler> createJoinNodeHandler(std::vector<std::string> parameters)
{
    std::shared_ptr<const Solvers::EvaluationMerger> merger = IO::Reader::getEvaluationMerger(parameters[1]);
    double percentMustBeEqual = std::stod(parameters[2]);

    if (parameters[0] == "staticOrder")
    {
        if (parameters[3] == "default")
            return std::make_shared<Solvers::StaticOrderJoinNodeHandler>(merger, percentMustBeEqual, Solvers::StaticOrderJoinNodeHandler::Order::defaultOrder);
        else if (parameters[3] == "gdf")
            return std::make_shared<Solvers::StaticOrderJoinNodeHandler>(merger, percentMustBeEqual, Solvers::StaticOrderJoinNodeHandler::Order::greatestDegreeFirst);
        else if (parameters[3] == "sdf")
            return std::make_shared<Solvers::StaticOrderJoinNodeHandler>(merger, percentMustBeEqual, Solvers::StaticOrderJoinNodeHandler::Order::smallestDegreeFirst);
        else if (parameters[3] == "random")
            return std::make_shared<Solvers::StaticOrderJoinNodeHandler>(merger, percentMustBeEqual, Solvers::StaticOrderJoinNodeHandler::Order::random);
        else
            throw std::runtime_error("Invalid order for static order join node handler: " + parameters[3] + "!");
    }
    else if (parameters[0] == "dynamicOrder")
    {
        if (parameters[3] == "mostColouredNeighbours")
            return std::make_shared<Solvers::DynamicOrderJoinNodeHandler>(merger, percentMustBeEqual, Solvers::DynamicOrderJoinNodeHandler::Order::mostColouredNeighboursFirst);
        else if (parameters[3] == "fewestColouredNeighboursFirst")
            return std::make_shared<Solvers::DynamicOrderJoinNodeHandler>(merger, percentMustBeEqual, Solvers::DynamicOrderJoinNodeHandler::Order::fewestColouredNeighboursFirst);
        else if (parameters[3] == "mostSameColouredNeighboursFirst")
            return std::make_shared<Solvers::DynamicOrderJoinNodeHandler>(merger, percentMustBeEqual, Solvers::DynamicOrderJoinNodeHandler::Order::mostSameColouredNeighboursFirst);
        else if (parameters[3] == "mostPercentSameColouredNeighboursFirst")
            return std::make_shared<Solvers::DynamicOrderJoinNodeHandler>(merger, percentMustBeEqual, Solvers::DynamicOrderJoinNodeHandler::Order::mostPercentSameColouredNeighboursFirst);
        else
            throw std::runtime_error("Invalid order for dynamic order join node handler: " + parameters[3] + "!");
    }
    else if (parameters[0] == "greedyColourBag")
    {
        return std::make_shared<Solvers::GreedyColourBagJoinNodeHandler>(merger, percentMustBeEqual);
    }
    else if (parameters[0] == "growthColourBag")
    {
        return std::make_shared<Solvers::GrowthColourBagJoinNodeHandler>(merger, percentMustBeEqual);
    }
    else if (parameters[0] == "useChildColours")
    {
        return std::make_shared<Solvers::UseChildColoursJoinNodeHandler>(merger, percentMustBeEqual);
    }
    throw std::runtime_error("Invalid join node handler identifier is given: " + parameters[0] + "!");
}

std::shared_ptr<Solvers::JoinNodeHandler> IO::Reader::readJoinNodeHandler(const std::string& str)
{
    return createJoinNodeHandler(splitParameters(str));
}

std::shared_ptr<Solvers::JoinNodeHandler> IO::Reader::readJoinNodeHandler(int argc, char** argv)
{
    std::string joinNodeHandler = getParameter(argc, argv, "--joinNodeHandler", true);
    std::vector<std::string> parameters;
    parameters.push_back(joinNodeHandler);
    parameters.push_back(getParameter(argc, argv, "--evaluationMerger", true));
    parameters.push_back(getParameter(argc, argv, "--percentMustBeEqual", true));
    //    if (joinNodeHandler == "greedyColourBag") {}
    //    if (joinNodeHandler == "growthColourBag") {}
    //    if (joinNodeHandler == "useChildColours") {}
    if (joinNodeHandler == "dynamicOrder")
        parameters.push_back(getParameter(argc, argv, "--dynamicOrder", true));
    if (joinNodeHandler == "staticOrder")
        parameters.push_back(getParameter(argc, argv, "--staticOrder", true));
    return createJoinNodeHandler(parameters);
}

std::shared_ptr<const Solvers::EvaluationMerger> IO::Reader::getEvaluationMerger(const std::string& str)
{
    if (str == "avg")
        return std::make_shared<Solvers::AverageEvaluationMerger>();
    else if (str == "max")
        return std::make_shared<Solvers::MaximumEvaluationMerger>();
    else if (str == "min")
        return std::make_shared<Solvers::MinimumEvaluationMerger>();
    else if (str == "sum")
        return std::make_shared<Solvers::SumEvaluationMerger>();
    else if (str == "product")
        return std::make_shared<Solvers::ProductEvaluationMerger>();

    throw std::runtime_error("Invalid evaluation merger identifier is given: " + str + "!");
}
