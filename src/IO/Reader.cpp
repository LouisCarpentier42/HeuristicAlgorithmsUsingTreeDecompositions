//
// Created by louis on 03/09/2021.
//
#include "Reader.h"

#include <utility>

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

std::vector<std::string> IO::Reader::tokenize(std::string& line)
{
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         back_inserter(tokens));
    return tokens;
}

int IO::Reader::convertToInt(std::string& str)
{
    int num;
    std::stringstream ss;
    ss << str;
    ss >> num;
    return num;
}
