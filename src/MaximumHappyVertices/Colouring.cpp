//
// Created by louis on 24/10/2021.
//

#include "Colouring.h"

#include <iostream> // TODO REMOVE

#include <algorithm>

Colouring::Colouring(DataStructures::Graph* graph, std::vector<colourType> initialColouring) :
    graph{graph},
    initialColouring{std::move(initialColouring)},
    nbColours{*std::max_element(this->initialColouring.begin(), this->initialColouring.end())},
    colouring{std::vector<colourType>(this->initialColouring)}
{}

colourType Colouring::getColour(vertexType vertex) const
{
    return colouring[vertex];
}

void Colouring::setColour(vertexType vertex, colourType colour)
{
    if (!isPrecoloured(vertex) && colour <= nbColours)
    {
        colouring[vertex] = colour;
    }
}

bool Colouring::isPrecoloured(vertexType vertex) const
{
    return initialColouring[vertex] != 0;
}

bool Colouring::isColoured(vertexType vertex) const
{
    return colouring[vertex] != 0;
}

unsigned int Colouring::getNbHappyVertices() const
{
    unsigned int nbHappyVertices{0};

    for (vertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        bool vertexIsHappy{true};
        for (vertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (colouring[neighbour] != colouring[vertex])
            {
                vertexIsHappy = false;
                break;
            }
        }
        if (vertexIsHappy)
        {
            nbHappyVertices++;
        }
    }
    return nbHappyVertices;
}
