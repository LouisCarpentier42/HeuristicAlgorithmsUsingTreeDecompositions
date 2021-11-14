//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_LEAFBAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_LEAFBAG_H

#include "NiceBag.h"

namespace DataStructures
{
    class LeafBag : public NiceBag
    {
    public:
        explicit LeafBag(int id);

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_LEAFBAG_H
