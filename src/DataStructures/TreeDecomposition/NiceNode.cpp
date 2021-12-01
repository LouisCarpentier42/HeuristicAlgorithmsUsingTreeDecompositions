//
// Created by louis on 10/11/2021.
//

#include "NiceNode.h"

DataStructures::NiceNode::NiceNode(int id, size_t size, BagContent bagContent, ChildVector childVector, NodeType type)
    : Node(id, size, std::move(bagContent), std::move(childVector)), bagType{type}
{}

DataStructures::NodeType DataStructures::NiceNode::getNodeType() const
{
    return bagType;
}