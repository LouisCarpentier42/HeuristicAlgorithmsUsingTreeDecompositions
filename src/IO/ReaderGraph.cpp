//
// Created by louis on 11/11/2021.
//

#include "Reader.h"

DataStructures::Graph IO::Reader::readGraph(const std::string &filename) const
{
    std::ifstream file{graphFilesDir + filename};
    if (!file)
    {
        throw std::runtime_error("Can't read graph in '" + filename + "' because the file can't be opened!");
    }

    std::string line{"c"};
    while (file && line[0] != 'p')
    {
        std::getline(file, line);
    }

    std::vector<std::string> tokens = tokenize(line);
    int nbVertices{convertToInt(tokens[2])};
    int nbEdges{convertToInt(tokens[3])};

    std::vector<std::vector<DataStructures::VertexType>> adjacencyList(nbVertices);

    std::getline(file, line);
    tokens = tokenize(line);
    while (file)
    {
        if (!(tokens.empty() || tokens[0] == "c"))
        {
            int vertex1{convertToInt(tokens[0])-1};
            int vertex2{convertToInt(tokens[1])-1};
            adjacencyList[vertex1].push_back(vertex2);
            adjacencyList[vertex2].push_back(vertex1);
        }
        std::getline(file, line);
        tokens = tokenize(line);
    }

    return DataStructures::Graph{static_cast<size_t>(nbVertices), adjacencyList};
}