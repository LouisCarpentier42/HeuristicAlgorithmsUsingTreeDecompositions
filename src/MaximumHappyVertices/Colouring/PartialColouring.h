//
// Created by louis on 24/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_PARTIALCOLOURING_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_PARTIALCOLOURING_H

#include "../../CustomTypes.h"

#include <iostream>
#include <vector>

namespace MaximumHappyVertices
{
    class PartialColouring
    {
    protected:
        std::vector<colourType> colouring;
        const colourType nbColours;

    public:
        explicit PartialColouring(std::vector<colourType> colouring);

        [[nodiscard]] size_t getNbVertices() const;
        [[nodiscard]] colourType getNbColours() const;
        [[nodiscard]] bool isColoured(vertexType vertex) const;
        [[nodiscard]] colourType getColour(vertexType vertex) const;
    };

    std::ostream& operator<<(std::ostream& out, const PartialColouring& colouring);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_PARTIALCOLOURING_H
