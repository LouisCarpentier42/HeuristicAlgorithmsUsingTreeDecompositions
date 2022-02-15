//
// Created by louis on 03/09/2021.
//
#include "Reader.h"

#include <cstring>
#include <sys/stat.h>


IO::Reader::Reader(
        const std::string& graphFilesDir,
        const std::string& g6GraphFilesDir,
        const std::string& treeDecompositionFilesDir,
        const std::string& experimentFilesDir,
        const std::string& resultFilesDir)
    : graphFilesDir{graphFilesDir},
      g6GraphFilesDir{g6GraphFilesDir},
      treeDecompositionFilesDir{treeDecompositionFilesDir},
      experimentFilesDir{experimentFilesDir},
      resultFilesDir{resultFilesDir}
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

void IO::Reader::createDirectory(const std::string& dir)
{
    if (!pathExists(dir))
    {
        system(("mkdir " + dir).c_str());
    }
}

bool IO::Reader::pathExists(const std::string& path)
{
    struct stat buffer{};
    return stat (path.c_str(), &buffer) == 0;
}
