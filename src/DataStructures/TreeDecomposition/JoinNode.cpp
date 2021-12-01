//
// Created by louis on 10/11/2021.
//

#include "JoinNode.h"

DataStructures::JoinNode::JoinNode(
        int id, size_t size, BagContent bagContent, NiceNode* leftChild, DataStructures::NiceNode* rightChild)
    : NiceNode(id, size, std::move(bagContent), ChildVector{leftChild, rightChild}, NodeType::JoinNode),
      leftChild{leftChild}, rightChild{rightChild}
{
    if (!leftChild || !rightChild) throw std::invalid_argument("A join vertex must have two existing children!");
}

const DataStructures::NiceNode *DataStructures::JoinNode::getLeftChild() const
{
    return leftChild;
}

const DataStructures::NiceNode *DataStructures::JoinNode::getRightChild() const
{
    return rightChild;
}

std::string DataStructures::JoinNode::getTypeString() const
{
    return "[Join Node]";
}
