//
// Created by louis on 24/10/2021.
//

#include "Colouring.h"

#include <algorithm>

MaximumHappyVertices::Colouring::Colouring(std::vector<colourType> initialColouring) :
    initialColouring{std::move(initialColouring)},
    nbColours{*std::max_element(this->initialColouring.begin(), this->initialColouring.end())},
    colouring{std::vector<colourType>(this->initialColouring)}
{}

colourType MaximumHappyVertices::Colouring::getNbColours() const
{
    return nbColours;
}

colourType MaximumHappyVertices::Colouring::getColour(vertexType vertex) const
{
    return colouring[vertex];
}

void MaximumHappyVertices::Colouring::setColour(vertexType vertex, colourType colour)
{
    if (!isPrecoloured(vertex) && colour <= nbColours)
    {
        colouring[vertex] = colour;
    }
}

bool MaximumHappyVertices::Colouring::isPrecoloured(vertexType vertex) const
{
    return initialColouring[vertex] != 0;
}

bool MaximumHappyVertices::Colouring::isColoured(vertexType vertex) const
{
    return colouring[vertex] != 0;
}
