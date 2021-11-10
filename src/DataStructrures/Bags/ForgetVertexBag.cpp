//
// Created by louis on 10/11/2021.
//

#include "ForgetVertexBag.h"

DataStructures::ForgetVertexBag::ForgetVertexBag(
    int id, size_t size, DataStructures::BagContent vertices, NiceBag* child, DataStructures::VertexType forgottenVertex)
    : IntroduceForgetVertexBagBase(id, size, std::move(vertices), child, DataStructures::BagType::ForgetVertexBag, forgottenVertex)
{}

DataStructures::VertexType DataStructures::ForgetVertexBag::getForgottenVertex() const
{
    return specialVertex;
}
