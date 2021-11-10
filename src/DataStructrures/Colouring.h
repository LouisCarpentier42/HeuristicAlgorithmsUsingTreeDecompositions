//
// Created by louis on 26/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H

#include "PartialColouring.h"

namespace DataStructures
{
    class Colouring : public PartialColouring
    {
    public:
        explicit Colouring(PartialColouring partialColouring);
        virtual void setColour(DataStructures::VertexType vertex, DataStructures::ColourType colour);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
