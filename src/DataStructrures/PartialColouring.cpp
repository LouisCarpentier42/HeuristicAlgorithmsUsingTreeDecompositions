//
// Created by louis on 24/10/2021.
//

#include "PartialColouring.h"

#include <algorithm>

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
