//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEVERTEXBAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEVERTEXBAG_H

#include "../Graph.h"
#include "IntroduceForgetVertexBagBase.h"

namespace DataStructures
{
    class IntroduceVertexBag : public IntroduceForgetVertexBagBase
    {
    public:
        IntroduceVertexBag(int id, size_t size, BagContent vertices, NiceBag* child, VertexType introducedVertex);

        [[nodiscard]] DataStructures::VertexType getIntroducedVertex() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEVERTEXBAG_H
