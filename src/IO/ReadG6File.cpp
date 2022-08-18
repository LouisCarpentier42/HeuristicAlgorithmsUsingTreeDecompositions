//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "Reader.h"

void IO::Reader::readG6File(const std::string& filename) const
{
    std::ifstream g6File{g6GraphFilesDir + filename};
    if (!g6File)
    {
        throw std::runtime_error("Can't read g6 graphs in '" + filename + "' because the file can't be opened!");
    }

    std::string outputDir = graphFilesDir + filename + "/";
    char command[256];
    sprintf(command, R"(mkdir %s)",outputDir.c_str());
    system(command);

    std::string line{};
    int graphNb{0};
    while (g6File)
    {
        graphNb++;

        std::vector<std::string> tokens = tokenize(line);
        while (tokens.empty() || tokens[0] != "Graph")
        {
            std::getline(g6File, line);
            tokens = tokenize(line);
        }

        std::getline(g6File, line);
        if (line.empty()) break;

        std::ofstream outputFile;
        outputFile.open(outputDir + "graph" + std::to_string(graphNb) + ".gr");
        outputFile << "c Generated from g6-file '" << filename << "'\n";
        outputFile << "p tw " << line << "\n";

        std::vector<std::string> edgeTokens{};
        std::getline(g6File, line);
        while (!line.empty())
        {
            std::vector<std::string> newEdgeTokens = tokenize(line);
            edgeTokens.insert(edgeTokens.end(), newEdgeTokens.begin(), newEdgeTokens.end());
            std::getline(g6File, line);
        }
        for (int i{0}; i < edgeTokens.size(); i+=2)
            outputFile << (convertToInt(edgeTokens[i])+1) << " " << (convertToInt(edgeTokens[i+1])+1) << "\n";

        outputFile.close();
    }
    g6File.close();
}