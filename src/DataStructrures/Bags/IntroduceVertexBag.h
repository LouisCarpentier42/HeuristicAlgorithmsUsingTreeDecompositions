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
        IntroduceVertexBag(int id, size_t size, BagContent bagContent, NiceBag* child, VertexType introducedVertex);

        [[nodiscard]] DataStructures::VertexType getIntroducedVertex() const;

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEVERTEXBAG_H
