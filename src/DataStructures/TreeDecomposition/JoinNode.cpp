//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "JoinNode.h"

DataStructures::JoinNode::JoinNode(
        int id, size_t size, BagContent bagContent, std::shared_ptr<NiceNode>& leftChild, std::shared_ptr<NiceNode>& rightChild)
    : NiceNode(id, size, std::move(bagContent), std::vector<std::shared_ptr<Node>>{leftChild, rightChild}, NodeType::JoinNode),
      leftChild{leftChild}, rightChild{rightChild}
{
    if (!leftChild || !rightChild) throw std::invalid_argument("A join vertex must have two existing children!");
}

std::shared_ptr<DataStructures::NiceNode> DataStructures::JoinNode::getLeftChild()
{
    return leftChild;
}

std::shared_ptr<DataStructures::NiceNode> DataStructures::JoinNode::getRightChild()
{
    return rightChild;
}

std::string DataStructures::JoinNode::getTypeString() const
{
    return "[Join Node]";
}
