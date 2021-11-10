//
// Created by louis on 26/10/2021.
//

#include "Colouring.h"

#include <algorithm>

DataStructures::Colouring::Colouring(DataStructures::PartialColouring partialColouring) :
    PartialColouring{std::move(partialColouring)}
{}

void DataStructures::Colouring::setColour(DataStructures::VertexType vertex, DataStructures::ColourType colour)
{
    if (colour <= nbColours)
        colouring[vertex] = colour;
}
