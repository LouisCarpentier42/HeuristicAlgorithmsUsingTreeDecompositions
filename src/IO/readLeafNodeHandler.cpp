//
// Created by louis on 12/02/2022.
//

#include "Reader.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/LeafNodeHandler/ConcreteLeafNodeHandlers.h"

Solvers::LeafNodeHandler* createLeafNodeHandler(std::vector<std::string> parameters)
{
    if (parameters[0] == "passive")
        return new Solvers::PassiveLeafNodeHandlers{};
    throw std::runtime_error("Invalid leaf node handler identifier is given: " + parameters[0] + "!");
}

Solvers::LeafNodeHandler* IO::Reader::readLeafNodeHandler(const std::string& str)
{
    return createLeafNodeHandler(splitParameters(str));
}

Solvers::LeafNodeHandler* IO::Reader::readLeafNodeHandler(int argc, char** argv)
{
    std::string leafNodeHandler = getParameter(argc, argv, "--leafNodeHandler", true);
    std::vector<std::string> parameters;
    parameters.push_back(leafNodeHandler);
    //    if (leafNodeHandler == "passive") {}

    return createLeafNodeHandler(parameters);
}