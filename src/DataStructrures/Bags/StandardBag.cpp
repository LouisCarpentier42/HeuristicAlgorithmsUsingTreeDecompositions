//
// Created by louis on 10/11/2021.
//

#include "StandardBag.h"

DataStructures::StandardBag::StandardBag(int id, size_t size, DataStructures::BagContent bagContent)
    : Bag(id, size, std::move(bagContent), ChildVector())
{}

void DataStructures::StandardBag::addChild(StandardBag* child)
{
    childVector.push_back(child);
    child->setParent(this);
}