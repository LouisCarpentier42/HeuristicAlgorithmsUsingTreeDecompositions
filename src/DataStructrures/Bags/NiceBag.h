//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICEBAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICEBAG_H

#include "Bag.h"

namespace DataStructures // TODO add special leaf bag
{
    enum class BagType {
        LeafBag,
        ForgetVertexBag,
        IntroduceVertexBag,
        JoinBag
    };

    class NiceBag : public Bag
    {
    private:
        const BagType bagType;

    protected:
        NiceBag(int id, size_t size, BagContent vertices, ChildVector childVector, BagType bagType);

    public:
        [[nodiscard]] BagType getBagType();
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICEBAG_H
