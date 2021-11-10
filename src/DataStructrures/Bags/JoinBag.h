//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINBAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINBAG_H

#include "NiceBag.h"

namespace DataStructures
{
    class JoinBag : public NiceBag
    {
    private:
        const NiceBag* leftChild;
        const NiceBag* rightChild;

    public:
        JoinBag(int id, size_t size, BagContent vertices, NiceBag* leftChild, NiceBag* rightChild);

        [[nodiscard]] const NiceBag* getLeftChild();
        [[nodiscard]] const NiceBag* getRightChild();
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINBAG_H
