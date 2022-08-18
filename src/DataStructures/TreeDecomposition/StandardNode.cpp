//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "StandardNode.h"

DataStructures::StandardNode::StandardNode(int id, size_t size, DataStructures::BagContent bagContent)
    : Node(id, size, std::move(bagContent), std::vector<std::shared_ptr<Node>>())
{}

void DataStructures::StandardNode::addChild(std::shared_ptr<StandardNode>& child)
{
    childVector.push_back(child);
}