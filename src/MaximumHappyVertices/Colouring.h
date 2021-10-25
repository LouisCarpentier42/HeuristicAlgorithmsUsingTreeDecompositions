//
// Created by louis on 24/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H

#include "../CustomTypes.h"

#include <vector>

namespace MaximumHappyVertices
{
    class Colouring
    {
    private:
        const std::vector<colourType> initialColouring;
        const colourType nbColours;
        std::vector<colourType> colouring;

    public:
        explicit Colouring(std::vector<colourType> initialColouring);

        [[nodiscard]] colourType getNbColours() const;
        [[nodiscard]] colourType getColour(vertexType vertex) const;
        void setColour(vertexType vertex, colourType colour);
        [[nodiscard]] bool isPrecoloured(vertexType vertex) const;
        [[nodiscard]] bool isColoured(vertexType vertex) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
