//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "IntroduceForgetNodeBase.h"

DataStructures::IntroduceForgetNodeBase::IntroduceForgetNodeBase(
        int id, size_t size, BagContent bagContent, std::shared_ptr<NiceNode>& child, NodeType bagType, VertexType specialVertex)
    : NiceNode(id, size, std::move(bagContent), std::vector<std::shared_ptr<Node>>{child}, bagType),
      child{child}, specialVertex{specialVertex}
{
    if (!child) throw std::invalid_argument("An introduce and forget vertex bag must have an existing child!");
}

std::shared_ptr<DataStructures::NiceNode> DataStructures::IntroduceForgetNodeBase::getChild()
{
    return child;
}