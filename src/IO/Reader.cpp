//
// Created by louis on 03/09/2021.
//
#include "Reader.h"

#include <cstring>


IO::Reader::Reader(
        std::string graphFilesDir,
        std::string g6GraphFilesDir,
        std::string treeDecompositionFilesDir,
        std::string experimentFilesDir,
        std::string resultFilesDir)
    : graphFilesDir{std::move(graphFilesDir)},
      g6GraphFilesDir{std::move(g6GraphFilesDir)},
      treeDecompositionFilesDir{std::move(treeDecompositionFilesDir)},
      experimentFilesDir{std::move(experimentFilesDir)},
      resultFilesDir{std::move(resultFilesDir)}
{}


std::string IO::Reader::getParameter(int argc, char** argv, const std::string& paramName, bool isObligatedParam)
{
    for (int i{0}; i < argc-1; i++)
    {
        if (strcmp(argv[i], paramName.c_str()) == 0)
        {
            return std::string{argv[i+1]};
        }
    }

    if (isObligatedParam)
        throw std::runtime_error("Obligated parameter '" + std::string(paramName) + "' is not specified!");

    return std::string{};
}

std::vector<std::string> IO::Reader::tokenize(const std::string& line)
{
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         back_inserter(tokens));
    return tokens;
}

int IO::Reader::convertToInt(const std::string& str)
{
    int num;
    std::stringstream ss;
    ss << str;
    ss >> num;
    return num;
}

std::vector<std::string> IO::Reader::splitParameters(const std::string& str)
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