//
// Created by louis on 24/10/2021.
//

#include "PartialColouring.h"

#include <algorithm>
#include <random>

MaximumHappyVertices::PartialColouring::PartialColouring(std::vector<colourType> colouring) :
    colouring{std::move(colouring)},
    nbColours{*std::max_element(this->colouring.begin(), this->colouring.end())}
{}

size_t MaximumHappyVertices::PartialColouring::getNbVertices() const
{
    return colouring.size();
}

colourType MaximumHappyVertices::PartialColouring::getNbColours() const
{
    return nbColours;
}

bool MaximumHappyVertices::PartialColouring::isColoured(vertexType vertex) const
{
    return colouring[vertex] != 0;
}

colourType MaximumHappyVertices::PartialColouring::getColour(vertexType vertex) const
{
    return colouring[vertex];
}

std::ostream& MaximumHappyVertices::operator<<(std::ostream& out, const MaximumHappyVertices::PartialColouring& colouring)
{
    out << "Colouring: [" << colouring.getColour(0);
    for (vertexType vertex{1}; vertex<colouring.getNbVertices(); vertex++) {
        out << ", " << colouring.getColour(vertex);
    }
    return out << "]";
}

MaximumHappyVertices::PartialColouring MaximumHappyVertices::generatePartialColouring(DataStructures::Graph& graph, int nbColours, double percentColouredVertices)
{
    static std::mt19937 rng;
    std::uniform_int_distribution<colourType> colourDistribution(1, nbColours);

    // Create a random shuffling of the vertices and colour them in this order
    std::vector<vertexType> allVertices(graph.getNbVertices());
    for (vertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
        allVertices.push_back(vertex);
    std::shuffle(allVertices.begin(), allVertices.end(), rng);

    // Colour the first nbColours vertices in each colour before randomly colour the remaining vertices
    std::vector<colourType> colourVector(graph.getNbVertices());
    for (int i{0}; i < nbColours; i++)
        colourVector[allVertices[i]] = i+1;
    for (int i{0}; i < percentColouredVertices * graph.getNbVertices(); i++)
        colourVector[allVertices[i]] = colourDistribution(rng);

    return PartialColouring{colourVector};
}

