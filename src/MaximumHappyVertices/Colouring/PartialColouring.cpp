//
// Created by louis on 24/10/2021.
//

#include "PartialColouring.h"

#include <algorithm>

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

