//
// Created by louis on 24/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_PARTIALCOLOURING_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_PARTIALCOLOURING_H

#include "DataStructuresAliases.h"

#include <iostream>
#include <vector>

namespace DataStructures
{
    class PartialColouring
    {
    protected:
        std::vector<DataStructures::ColourType> colouring;
        const size_t nbColours;

    public:
        explicit PartialColouring(std::vector<DataStructures::ColourType> colouring);

        [[nodiscard]] size_t getNbVertices() const;
        [[nodiscard]] size_t getNbColours() const;
        [[nodiscard]] bool isColoured(DataStructures::VertexType vertex) const;
        [[nodiscard]] DataStructures::ColourType getColour(DataStructures::VertexType vertex) const;
    };

    std::ostream& operator<<(std::ostream& out, const PartialColouring& colouring);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_PARTIALCOLOURING_H
