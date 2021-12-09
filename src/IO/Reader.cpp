//
// Created by louis on 03/09/2021.
//
#include "Reader.h"

IO::Reader::Reader(std::string graphFilesDir, std::string treeDecompositionFilesDir, std::string experimentFilesDir)
    : graphFilesDir{std::move(graphFilesDir)},
      treeDecompositionFilesDir{std::move(treeDecompositionFilesDir)},
      experimentFilesDir{std::move(experimentFilesDir)}
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
