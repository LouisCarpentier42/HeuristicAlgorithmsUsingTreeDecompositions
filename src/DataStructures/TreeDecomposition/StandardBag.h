//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_STANDARDBAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_STANDARDBAG_H

#include "Bag.h"

namespace DataStructures
{
    class StandardBag : public Bag
    {
    public:
        StandardBag(int id, size_t size, BagContent bagContent);

        void addChild(StandardBag* child);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_STANDARDBAG_H
