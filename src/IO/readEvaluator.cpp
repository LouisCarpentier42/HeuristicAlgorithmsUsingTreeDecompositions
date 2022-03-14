//
// Created by louis on 12/02/2022.
//

#include "Reader.h"
#include "../DataStructures/Evaluator/potentialHappyMHVEvaluator.h"
#include "../DataStructures/Evaluator/GrowthMHVEvaluator.h"

std::shared_ptr<DataStructures::Evaluator> createEvaluator(std::vector<std::string> parameters)
{
    if (parameters[0] == "basicMHVEvaluator")
        return std::make_shared<DataStructures::BasicMHVEvaluator>();
    else if (parameters[0] == "potentialHappyMHVEvaluator")
        return std::make_shared<DataStructures::potentialHappyMHVEvaluator>(
            IO::Reader::convertToInt(parameters[1]),
            IO::Reader::convertToInt(parameters[2]),
            IO::Reader::convertToInt(parameters[3])
        );
    else if (parameters[0] == "growthMHVEvaluator")
        return std::make_shared<DataStructures::GrowthMHVEvaluator>(
            IO::Reader::convertToInt(parameters[1]),
            IO::Reader::convertToInt(parameters[2]),
            IO::Reader::convertToInt(parameters[3]),
            IO::Reader::convertToInt(parameters[4]),
            IO::Reader::convertToInt(parameters[5]),
            IO::Reader::convertToInt(parameters[6]),
            IO::Reader::convertToInt(parameters[7])
        );
    throw std::runtime_error("Invalid evaluator identifier is given: " + parameters[0] + "!");
}

std::shared_ptr<DataStructures::Evaluator> IO::Reader::readEvaluator(const std::string& str)
{
    return createEvaluator(splitParameters(str));
}

std::shared_ptr<DataStructures::Evaluator> IO::Reader::readEvaluator(int argc, char** argv)
{
    std::string evaluator = getParameter(argc, argv, "--evaluator", true);
    std::vector<std::string> parameters;
    parameters.push_back(evaluator);
    // if (evaluator == "basicMHVEvaluator) {}
    if (evaluator == "potentialHappyMHVEvaluator")
    {
        parameters.push_back(getParameter(argc, argv, "--happyVertexWeight", true));
        parameters.push_back(getParameter(argc, argv, "--potentialHappyVertexWeight", true));
        parameters.push_back(getParameter(argc, argv, "--unhappyVertexWeight", true));
    }
    if (evaluator == "growthMHVEvaluator")
    {
        parameters.push_back(getParameter(argc, argv, "--HWeight", true));
        parameters.push_back(getParameter(argc, argv, "--UWeight", true));
        parameters.push_back(getParameter(argc, argv, "--PWeight", true));
        parameters.push_back(getParameter(argc, argv, "--LPWeight", true));
        parameters.push_back(getParameter(argc, argv, "--LHWeight", true));
        parameters.push_back(getParameter(argc, argv, "--LUWeight", true));
        parameters.push_back(getParameter(argc, argv, "--LFWeight", true));
    }
    return createEvaluator(parameters);
}