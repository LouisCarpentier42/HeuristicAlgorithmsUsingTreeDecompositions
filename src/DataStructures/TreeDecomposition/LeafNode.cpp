//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "LeafNode.h"

DataStructures::LeafNode::LeafNode(int id)
    : NiceNode(id, 0, BagContent{}, std::vector<std::shared_ptr<Node>>{}, NodeType::LeafNode)
{}

std::string DataStructures::LeafNode::getTypeString() const
{
    return "[Leaf Node]";
}
