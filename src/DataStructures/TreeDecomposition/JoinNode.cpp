//
// Created by louis on 10/11/2021.
//

#include "JoinNode.h"

DataStructures::JoinNode::JoinNode(
        int id, size_t size, BagContent bagContent, NiceNode* leftChild, DataStructures::NiceNode* rightChild)
    : NiceNode(id, size, std::move(bagContent), std::vector<Node*>{leftChild, rightChild}, NodeType::JoinNode),
      leftChild{leftChild}, rightChild{rightChild}
{
    if (!leftChild || !rightChild) throw std::invalid_argument("A join vertex must have two existing children!");
}

DataStructures::NiceNode *DataStructures::JoinNode::getLeftChild()
{
    return leftChild;
}

DataStructures::NiceNode *DataStructures::JoinNode::getRightChild()
{
    return rightChild;
}

std::string DataStructures::JoinNode::getTypeString() const
{
    return "[Join Node]";
}
