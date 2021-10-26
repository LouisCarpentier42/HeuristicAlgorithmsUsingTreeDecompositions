//
// Created by louis on 26/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H

#include "../../CustomTypes.h"
#include "PartialColouring.h"

namespace MaximumHappyVertices
{
    class Colouring : public PartialColouring
    {
    public:
        explicit Colouring(PartialColouring partialColouring);
        virtual void setColour(vertexType vertex, colourType colour);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
