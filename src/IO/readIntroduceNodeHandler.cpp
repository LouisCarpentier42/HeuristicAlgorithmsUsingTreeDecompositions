//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "Reader.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/IntroduceNodeHandler/ConcreteIntroduceNodeHandlers.h"


std::shared_ptr<Solvers::IntroduceNodeHandler> createIntroduceNodeHandler(std::vector<std::string> parameters)
{
    if (parameters[0] == "bestColour")
        return std::make_shared<Solvers::BestColourIntroduceNodeHandler>();
    else if (parameters[0] == "greedy")
        return std::make_shared<Solvers::GreedyIntroduceNodeHandler>();
    throw std::runtime_error("Invalid introduce node handler identifier is given: " + parameters[0] + "!");
}

std::shared_ptr<Solvers::IntroduceNodeHandler> IO::Reader::readIntroduceNodeHandler(const std::string& str)
{
    return createIntroduceNodeHandler(splitParameters(str));
}

std::shared_ptr<Solvers::IntroduceNodeHandler> IO::Reader::readIntroduceNodeHandler(int argc, char** argv)
{
    std::string introduceNodeHandler = getParameter(argc, argv, "--introduceNodeHandler", true);
    std::vector<std::string> parameters;
    parameters.push_back(introduceNodeHandler);
    //    if (introduceNodeHandler == "bestColour") {}
    //    if (introduceNodeHandler == "greedy") {}

    return createIntroduceNodeHandler(parameters);
}