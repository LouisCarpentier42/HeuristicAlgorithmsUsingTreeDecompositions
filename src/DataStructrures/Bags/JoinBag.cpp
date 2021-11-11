//
// Created by louis on 10/11/2021.
//

#include "JoinBag.h"

DataStructures::JoinBag::JoinBag(
        int id, size_t size, BagContent bagContent, NiceBag* leftChild, DataStructures::NiceBag* rightChild)
    : NiceBag(id, size, std::move(bagContent), ChildVector{leftChild, rightChild}, BagType::JoinBag),
      leftChild{leftChild}, rightChild{rightChild}
{
    if (!leftChild || !rightChild) throw std::invalid_argument("A join vertex must have two existing children!");
}

const DataStructures::NiceBag *DataStructures::JoinBag::getLeftChild()
{
    return leftChild;
}

const DataStructures::NiceBag *DataStructures::JoinBag::getRightChild()
{
    return rightChild;
}

std::string DataStructures::JoinBag::getTypeString() const
{
    return "[Join Node]";
}
