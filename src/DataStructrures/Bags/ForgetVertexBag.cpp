//
// Created by louis on 10/11/2021.
//

#include "ForgetVertexBag.h"

DataStructures::ForgetVertexBag::ForgetVertexBag(
        int id, size_t size, DataStructures::BagContent bagContent, NiceBag* child, DataStructures::VertexType forgottenVertex)
    : IntroduceForgetVertexBagBase(id, size, std::move(bagContent), child, DataStructures::BagType::ForgetVertexBag, forgottenVertex)
{}

DataStructures::VertexType DataStructures::ForgetVertexBag::getForgottenVertex() const
{
    return specialVertex;
}

std::string DataStructures::ForgetVertexBag::getTypeString() const
{
    return std::string("[Forget Vertex ") + std::to_string(specialVertex) + std::string(" Node]");
}