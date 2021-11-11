//
// Created by louis on 10/11/2021.
//

#include "IntroduceForgetVertexBagBase.h"

DataStructures::IntroduceForgetVertexBagBase::IntroduceForgetVertexBagBase(
        int id, size_t size, BagContent bagContent, NiceBag* child, BagType bagType, VertexType specialVertex)
    : NiceBag(id, size, std::move(bagContent), ChildVector{child}, bagType),
      child{child}, specialVertex{specialVertex}
{
    if (!child) throw std::invalid_argument("An introduce and forget vertex bag must have an existing child!");
}

const DataStructures::NiceBag* DataStructures::IntroduceForgetVertexBagBase::getChild() const
{
    return child;
}