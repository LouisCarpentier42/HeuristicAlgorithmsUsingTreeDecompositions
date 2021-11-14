//
// Created by louis on 26/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MUTABLECOLOURING_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MUTABLECOLOURING_H

#include "Colouring.h"

namespace DataStructures
{
    class MutableColouring : public Colouring
    {
    public:
        explicit MutableColouring(Colouring colouring);
        virtual void setColour(DataStructures::VertexType vertex, DataStructures::ColourType colour);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MUTABLECOLOURING_H
