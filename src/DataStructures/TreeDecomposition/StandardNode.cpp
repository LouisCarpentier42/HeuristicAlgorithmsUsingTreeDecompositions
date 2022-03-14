//
// Created by louis on 10/11/2021.
//

#include "StandardNode.h"

DataStructures::StandardNode::StandardNode(int id, size_t size, DataStructures::BagContent bagContent)
    : Node(id, size, std::move(bagContent), std::vector<std::shared_ptr<Node>>())
{}

void DataStructures::StandardNode::addChild(std::shared_ptr<StandardNode>& child)
{
    childVector.push_back(child);
}