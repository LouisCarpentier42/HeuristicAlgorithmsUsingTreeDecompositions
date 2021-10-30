//
// Created by louis on 26/10/2021.
//

#include "Colouring.h"

#include <algorithm>

MaximumHappyVertices::Colouring::Colouring(MaximumHappyVertices::PartialColouring partialColouring) :
    PartialColouring{std::move(partialColouring)}
{}

void MaximumHappyVertices::Colouring::setColour(vertexType vertex, colourType colour)
{
    if (colour <= nbColours)
        colouring[vertex] = colour;
}
