//
// Created by louis on 12/02/2022.
//

#include "Reader.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/ForgetNodeHandler/ConcreteForgetNodeHandlers.h"

std::shared_ptr<Solvers::ForgetNodeHandler> createForgetNodeHandler(std::vector<std::string> parameters)
{
    if (parameters[0] == "passive")
        return std::make_shared<Solvers::PassiveForgetNodeHandler>();
    else if (parameters[0] == "bestColour")
        return std::make_shared<Solvers::BestColourForgetNodeHandler>();
    throw std::runtime_error("Invalid forget node handler identifier is given: " + parameters[0] + "!");
}

std::shared_ptr<Solvers::ForgetNodeHandler> IO::Reader::readForgetNodeHandler(const std::string& str)
{
    return createForgetNodeHandler(splitParameters(str));
}

std::shared_ptr<Solvers::ForgetNodeHandler> IO::Reader::readForgetNodeHandler(int argc, char** argv)
{
    std::string forgetNodeHandler = getParameter(argc, argv, "--forgetNodeHandler", true);
    std::vector<std::string> parameters;
    parameters.push_back(forgetNodeHandler);
//    if (forgetNodeHandler == "passive") {}
//    if (forgetNodeHandler == "bestColour") {}

    return createForgetNodeHandler(parameters);
}


