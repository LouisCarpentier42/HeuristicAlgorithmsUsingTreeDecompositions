//
// Created by louis on 10/11/2021.
//

#include "StandardNode.h"

DataStructures::StandardNode::StandardNode(int id, size_t size, DataStructures::BagContent bagContent)
    : Node(id, size, std::move(bagContent), ChildVector())
{}

void DataStructures::StandardNode::addChild(StandardNode* child)
{
    childVector.push_back(child);
    child->setParent(this);
}