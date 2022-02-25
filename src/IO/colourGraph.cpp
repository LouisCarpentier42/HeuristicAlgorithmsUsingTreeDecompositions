//
// Created by louis on 12/02/2022.
//

#include "Reader.h"
#include "../rng.h"

void colourGraphRandom(int nbColours, double percentColouredVertices, DataStructures::Graph* graph)
{
    std::uniform_int_distribution<DataStructures::ColourType> colourDistribution(1, nbColours);

    // Create a random shuffling of the vertices and colour them in this order
    std::vector<DataStructures::VertexType> allVertices(graph->getNbVertices());
    std::iota(allVertices.begin(), allVertices.end(), 0);
    std::shuffle(allVertices.begin(), allVertices.end(), RNG::rng);

    // Colour the first nbColours vertices in each colour before randomly colour the remaining vertices
    for (int i{0}; i < nbColours; i++)
        graph->setInitialColour(allVertices[i], i+1);
    size_t nbVerticesToColour{static_cast<size_t>(percentColouredVertices * static_cast<double>(graph->getNbVertices()))};
    for (int i{nbColours}; i < nbVerticesToColour; i++)
        graph->setInitialColour(allVertices[i], colourDistribution(RNG::rng));
}

std::string IO::Reader::colourGraph(const std::string& str, DataStructures::Graph* graph)
{
    std::vector<std::string> parameters = splitParameters(str);
    if (parameters[0] == "generated")
    {
        return "generated";
    }
    if (parameters[0] == "random")
    {
        int nbColours{IO::Reader::convertToInt(parameters[1])};
        double percentColouredVertices{std::stod(parameters[2])};

        colourGraphRandom(nbColours, percentColouredVertices, graph);
        return "random";
    }

    throw std::runtime_error("Invalid colouring identifier is given: " + str + "!");
}

std::string IO::Reader::colourGraph(int argc, char** argv, DataStructures::Graph* graph)
{
    std::string colouring = getParameter(argc, argv, "--colouring", true);
    if (colouring == "random")
    {
        colourGraphRandom(
            convertToInt(getParameter(argc, argv, "--nbColours", true)),
            std::strtod(getParameter(argc, argv, "--percentColouredVertices", true).c_str(), nullptr),
            graph
        );
        return "random";
    }

    throw std::runtime_error("Invalid colouring identifier is given: " + colouring + "!");
}
