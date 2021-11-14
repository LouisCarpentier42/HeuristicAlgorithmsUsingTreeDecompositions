//
// Created by louis on 24/10/2021.
//

#include "Colouring.h"

#include <algorithm>

DataStructures::Colouring::Colouring(std::vector<DataStructures::ColourType> colouring) :
    colouring{std::move(colouring)},
    nbColours{*std::max_element(this->colouring.begin(), this->colouring.end())}
{}

DataStructures::Colouring::Colouring(const DataStructures::Colouring* colouring) // TODO colouring vector is put correctly?
    : colouring{colouring->colouring}, nbColours{colouring->nbColours}
{}

size_t DataStructures::Colouring::getNbVertices() const
{
    return colouring.size();
}

size_t DataStructures::Colouring::getNbColours() const
{
    return nbColours;
}

bool DataStructures::Colouring::isColoured(DataStructures::VertexType vertex) const
{
    return colouring[vertex] != 0;
}

DataStructures::ColourType DataStructures::Colouring::getColour(DataStructures::VertexType vertex) const
{
    return colouring[vertex];
}

bool DataStructures::Colouring::operator==(const DataStructures::Colouring &other) const
{
    return colouring == other.colouring;
}

std::ostream& DataStructures::operator<<(std::ostream& out, const DataStructures::Colouring& colouring)
{
    out << "[" << colouring.getColour(0);
    for (DataStructures::VertexType vertex{1}; vertex<colouring.getNbVertices(); vertex++) {
        out << ", " << colouring.getColour(vertex);
    }
    return out << "]";
}
