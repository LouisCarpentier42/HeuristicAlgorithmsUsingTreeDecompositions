//
// Created by louis on 10/11/2021.
//

#include "LeafBag.h"

DataStructures::LeafBag::LeafBag(int id)
    : NiceBag(id, 0, BagContent{}, ChildVector{}, BagType::LeafBag)
{}

std::string DataStructures::LeafBag::getTypeString() const
{
    return "[Leaf Node]";
}
