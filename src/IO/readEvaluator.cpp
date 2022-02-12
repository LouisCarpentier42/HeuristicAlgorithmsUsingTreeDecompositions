//
// Created by louis on 12/02/2022.
//

#include "Reader.h"
#include "../DataStructures/Evaluator/PotentialHappyColouredMHVEvaluator.h"
#include "../DataStructures/Evaluator/PotentialHappyUncolouredMHVEvaluator.h"

const DataStructures::Evaluator* createEvaluator(std::vector<std::string> parameters)
{
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
    throw std::runtime_error("Invalid evaluator identifier is given: " + parameters[0] + "!");
}

const DataStructures::Evaluator* IO::Reader::readEvaluator(const std::string& str)
{
    return createEvaluator(splitParameters(str));
}

const DataStructures::Evaluator* IO::Reader::readEvaluator(int argc, char** argv)
{
    std::string evaluator = getParameter(argc, argv, "--evaluator", true);
    std::vector<std::string> parameters;
    parameters.push_back(evaluator);
    // if (evaluator == "basicMHVEvaluator) {}
    if (evaluator == "colouredMHVEvaluator")
    {
        parameters.push_back(getParameter(argc, argv, "--happyVertexWeight", true));
        parameters.push_back(getParameter(argc, argv, "--potentiallyHappyVertexWeight", true));
        parameters.push_back(getParameter(argc, argv, "--unhappyVertexWeight", true));
    }
    if (evaluator == "uncolouredMHVEvaluator")
    {
        parameters.push_back(getParameter(argc, argv, "--happyColouredVertexWeight", true));
        parameters.push_back(getParameter(argc, argv, "--potentiallyHappyColouredVertexWeight", true));
        parameters.push_back(getParameter(argc, argv, "--unhappyColouredVertexWeight", true));
        parameters.push_back(getParameter(argc, argv, "--happyUncolouredVertexWeight", true));
        parameters.push_back(getParameter(argc, argv, "--potentiallyHappyUncolouredVertexWeight", true));
        parameters.push_back(getParameter(argc, argv, "--unhappyUncolouredVertexWeight", true));
    }
    return createEvaluator(parameters);
}