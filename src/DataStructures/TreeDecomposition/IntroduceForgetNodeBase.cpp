//
// Created by louis on 10/11/2021.
//

#include "IntroduceForgetNodeBase.h"

DataStructures::IntroduceForgetNodeBase::IntroduceForgetNodeBase(
        int id, size_t size, BagContent bagContent, NiceNode* child, NodeType bagType, VertexType specialVertex)
    : NiceNode(id, size, std::move(bagContent), ChildVector{child}, bagType),
      child{child}, specialVertex{specialVertex}
{
    if (!child) throw std::invalid_argument("An introduce and forget vertex bag must have an existing child!");
}

const DataStructures::NiceNode* DataStructures::IntroduceForgetNodeBase::getChild() const
{
    return child;
}