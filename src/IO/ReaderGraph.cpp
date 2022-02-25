//
// Created by louis on 11/11/2021.
//

#include "Reader.h"

DataStructures::Graph* IO::Reader::readGraph(const std::string &filename) const
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
    std::string id{tokens[1]};
    int nbVertices{convertToInt(tokens[2])};
    int nbEdges{convertToInt(tokens[3])};

    std::vector<DataStructures::Vertex> vertices;
    for (DataStructures::VertexType vertexId{0}; vertexId < nbVertices; vertexId++)
        vertices.emplace_back(DataStructures::Vertex{vertexId});

    std::getline(file, line);
    tokens = tokenize(line);
    while (file)
    {
        if (!(tokens.empty() || tokens[0] == "c"))
        {
            if (id == "tw")
            {
                int vertex1{convertToInt(tokens[0])-1};
                int vertex2{convertToInt(tokens[1])-1};

                vertices[vertex1].degree++;
                vertices[vertex1].neighbours.push_back(vertex2);

                vertices[vertex2].degree++;
                vertices[vertex2].neighbours.push_back(vertex1);
            }
            else if (id == "edge")
            {
                if (tokens[0] == "e") // New edge
                {
                    int vertex1{convertToInt(tokens[1])-1};
                    int vertex2{convertToInt(tokens[2])-1};

                    vertices[vertex1].degree++;
                    vertices[vertex1].neighbours.push_back(vertex2);

                    vertices[vertex2].degree++;
                    vertices[vertex2].neighbours.push_back(vertex1);
                }
                else if(tokens[0] == "n") // Colour vertex
                {
                    int vertex{convertToInt(tokens[1])-1};
                    int colour{convertToInt(tokens[2])};

                    vertices[vertex].colour = colour;
                    vertices[vertex].isPrecoloured = true;
                    vertices[vertex].isColoured = true;
                }
            }
            else
            {
                throw std::runtime_error("Illegal for id graph '" + id + "'!");
            }
        }
        std::getline(file, line);
        tokens = tokenize(line);
    }

    return new DataStructures::Graph{vertices};
}