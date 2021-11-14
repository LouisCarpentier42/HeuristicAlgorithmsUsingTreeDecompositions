//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICEBAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICEBAG_H

#include "Bag.h"

namespace DataStructures
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
        NiceBag(int id, size_t size, BagContent bagContent, ChildVector childVector, BagType bagType);

    public:
        [[nodiscard]] BagType getBagType() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICEBAG_H
