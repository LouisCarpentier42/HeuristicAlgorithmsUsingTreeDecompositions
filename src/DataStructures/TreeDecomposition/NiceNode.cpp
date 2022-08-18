//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "NiceNode.h"

DataStructures::NiceNode::NiceNode(int id, size_t size, BagContent bagContent, std::vector<std::shared_ptr<Node>> childVector, NodeType type)
    : Node(id, size, std::move(bagContent), std::move(childVector)), bagType{type}
{}

DataStructures::NodeType DataStructures::NiceNode::getNodeType() const
{
    return bagType;
}

DataStructures::DynamicProgrammingTable& DataStructures::NiceNode::getTable()
{
    return *table;
}
