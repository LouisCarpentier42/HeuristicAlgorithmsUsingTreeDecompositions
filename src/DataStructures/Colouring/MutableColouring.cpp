//
// Created by louis on 26/10/2021.
//

#include "MutableColouring.h"

#include <algorithm>

DataStructures::MutableColouring::MutableColouring(const DataStructures::Colouring* colouring)
    : Colouring{colouring}
{}

void DataStructures::MutableColouring::setColour(DataStructures::VertexType vertex, DataStructures::ColourType colour)
{
    if (colour <= nbColours)
        colouring[vertex] = colour;
}
