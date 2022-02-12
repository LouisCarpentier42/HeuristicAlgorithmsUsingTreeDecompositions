//
// Created by louis on 12/02/2022.
//

#include "Reader.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/IntroduceNodeHandler/ConcreteIntroduceNodeHandlers.h"


Solvers::IntroduceNodeHandler* createIntroduceNodeHandler(std::vector<std::string> parameters)
{
    if (parameters[0] == "bestColour")
        return new Solvers::BestColourIntroduceNodeHandler{};
    else if (parameters[0] == "greedy")
        return new Solvers::GreedyIntroduceNodeHandler{};
    throw std::runtime_error("Invalid introduce node handler identifier is given: " + parameters[0] + "!");
}

Solvers::IntroduceNodeHandler* IO::Reader::readIntroduceNodeHandler(const std::string& str)
{
    return createIntroduceNodeHandler(splitParameters(str));
}

Solvers::IntroduceNodeHandler* IO::Reader::readIntroduceNodeHandler(int argc, char** argv)
{
    std::string introduceNodeHandler = getParameter(argc, argv, "--introduceNodeHandler", true);
    std::vector<std::string> parameters;
    parameters.push_back(introduceNodeHandler);
    //    if (introduceNodeHandler == "bestColour") {}
    //    if (introduceNodeHandler == "greedy") {}

    return createIntroduceNodeHandler(parameters);
}