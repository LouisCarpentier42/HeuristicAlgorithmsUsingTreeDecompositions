//
// Created by louis on 10/11/2021.
//

#include "NiceBag.h"

DataStructures::NiceBag::NiceBag(int id, size_t size, BagContent vertices, ChildVector childVector, BagType type)
    : Bag(id, size, std::move(vertices), std::move(childVector)), bagType{type}
{}

DataStructures::BagType DataStructures::NiceBag::getBagType()
{
    return bagType;
}