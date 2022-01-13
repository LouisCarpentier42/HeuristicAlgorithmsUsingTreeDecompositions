//
// Created by louis on 10/11/2021.
//

#include "LeafNode.h"

DataStructures::LeafNode::LeafNode(int id)
    : NiceNode(id, 0, BagContent{}, std::vector<Node*>{}, NodeType::LeafNode)
{}

std::string DataStructures::LeafNode::getTypeString() const
{
    return "[Leaf Node]";
}
