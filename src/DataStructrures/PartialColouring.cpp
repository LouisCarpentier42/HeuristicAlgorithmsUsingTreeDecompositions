//
// Created by louis on 24/10/2021.
//

#include "PartialColouring.h"

#include <algorithm>
#include <random>

DataStructures::PartialColouring::PartialColouring(std::vector<DataStructures::ColourType> colouring) :
    colouring{std::move(colouring)},
    nbColours{*std::max_element(this->colouring.begin(), this->colouring.end())}
{}

size_t DataStructures::PartialColouring::getNbVertices() const
{
    return colouring.size();
}

size_t DataStructures::PartialColouring::getNbColours() const
{
    return nbColours;
}

bool DataStructures::PartialColouring::isColoured(DataStructures::VertexType vertex) const
{
    return colouring[vertex] != 0;
}

DataStructures::ColourType DataStructures::PartialColouring::getColour(DataStructures::VertexType vertex) const
{
    return colouring[vertex];
}

std::ostream& DataStructures::operator<<(std::ostream& out, const DataStructures::PartialColouring& colouring)
{
    out << "[" << colouring.getColour(0);
    for (DataStructures::VertexType vertex{1}; vertex<colouring.getNbVertices(); vertex++) {
        out << ", " << colouring.getColour(vertex);
    }
    return out << "]";
}

DataStructures::PartialColouring DataStructures::generatePartialColouring(DataStructures::Graph& graph, int nbColours, double percentColouredVertices)
{
    static std::mt19937 rng;
    std::uniform_int_distribution<DataStructures::ColourType> colourDistribution(1, nbColours);

    // Create a random shuffling of the vertices and colour them in this order
    std::vector<DataStructures::VertexType> allVertices(graph.getNbVertices());
    for (DataStructures::VertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
        allVertices[vertex] = vertex;
    std::shuffle(allVertices.begin(), allVertices.end(), rng);

    // Colour the first nbColours vertices in each colour before randomly colour the remaining vertices
    std::vector<DataStructures::ColourType> colourVector(graph.getNbVertices());
    for (int i{0}; i < nbColours; i++)
        colourVector[allVertices[i]] = i+1;
    for (int i{nbColours}; i < percentColouredVertices * graph.getNbVertices(); i++)
        colourVector[allVertices[i]] = colourDistribution(rng);

    return PartialColouring{colourVector};
}

