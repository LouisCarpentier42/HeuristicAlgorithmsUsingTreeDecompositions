//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_FORGETVERTEXBAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_FORGETVERTEXBAG_H

#include "../Graph/Graph.h"
#include "IntroduceForgetVertexBagBase.h"

namespace DataStructures
{
    class ForgetVertexBag : public IntroduceForgetVertexBagBase
    {
    public:
        ForgetVertexBag(int id, size_t size, BagContent bagContent, NiceBag* child, VertexType forgottenVertex);

        [[nodiscard]] DataStructures::VertexType getForgottenVertex() const;

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_FORGETVERTEXBAG_H
