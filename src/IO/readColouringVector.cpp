//
// Created by louis on 12/02/2022.
//

#include "Reader.h"
#include "../rng.h"

std::vector<DataStructures::ColourType> generateRandomColouring(int nbColours, double percentColouredVertices, const DataStructures::Graph* graph)
{
    std::uniform_int_distribution<DataStructures::ColourType> colourDistribution(1, nbColours);

    // Create a random shuffling of the vertices and colour them in this order
    std::vector<DataStructures::VertexType> allVertices(graph->getNbVertices());
    std::iota(allVertices.begin(), allVertices.end(), 0);
    std::shuffle(allVertices.begin(), allVertices.end(), RNG::rng);

    // Colour the first nbColours vertices in each colour before randomly colour the remaining vertices
    std::vector<DataStructures::ColourType> colourVector(graph->getNbVertices());
    for (int i{0}; i < nbColours; i++)
        colourVector[allVertices[i]] = i+1;
    size_t nbVerticesToColour{static_cast<size_t>(percentColouredVertices * static_cast<double>(graph->getNbVertices()))};
    for (int i{nbColours}; i < nbVerticesToColour; i++)
        colourVector[allVertices[i]] = colourDistribution(RNG::rng);

    return colourVector;
}

std::map<std::string, std::vector<DataStructures::ColourType>> IO::Reader::readColouringVector(const std::string& str, const DataStructures::Graph* graph)
{
    std::vector<std::string> parameters = splitParameters(str);
    if (parameters[0] == "random")
    {
        int nbColours{IO::Reader::convertToInt(parameters[1])};
        double percentColouredVertices{std::stod(parameters[2])};
        int nbColourings{IO::Reader::convertToInt(parameters[3])};
        std::map<std::string, std::vector<DataStructures::ColourType>> colourings{};
        for (int j{0}; j < nbColourings; j++)
        {
            std::vector<DataStructures::ColourType> colourVector = generateRandomColouring(nbColours, percentColouredVertices, graph);
            colourings["random(nbColours:" + std::to_string(nbColours) + ";" +
            "%colouredVertices:" + std::to_string(percentColouredVertices) + ";" +
            "generated:[" + std::to_string(j+1) + "/" + std::to_string(nbColourings) + "])"] = colourVector;
        }
        return colourings;
    }

    throw std::runtime_error("Invalid colouring identifier is given: " + str + "!");
}

std::vector<DataStructures::ColourType> IO::Reader::readColouringVector(int argc, char** argv, const DataStructures::Graph* graph)
{
    std::string colouring = getParameter(argc, argv, "--colouring", true);
    if (colouring == "random")
    {
        return generateRandomColouring(
                    convertToInt(getParameter(argc, argv, "--nbColours", true)),
                    std::strtod(getParameter(argc, argv, "--percentColouredVertices", true).c_str(), nullptr),
                    graph
                );
    }

    throw std::runtime_error("Invalid colouring identifier is given: " + colouring + "!");
}
