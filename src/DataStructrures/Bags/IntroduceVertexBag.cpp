//
// Created by louis on 10/11/2021.
//

#include "IntroduceVertexBag.h"

DataStructures::IntroduceVertexBag::IntroduceVertexBag(
        int id, size_t size, DataStructures::BagContent bagContent, NiceBag* child, DataStructures::VertexType introducedVertex)
        : IntroduceForgetVertexBagBase(id, size, std::move(bagContent), child, DataStructures::BagType::IntroduceVertexBag, introducedVertex)
{}

DataStructures::VertexType DataStructures::IntroduceVertexBag::getIntroducedVertex() const
{
    return specialVertex;
}

std::string DataStructures::IntroduceVertexBag::getTypeString() const
{
    return std::string("[Introduce Vertex ") + std::to_string(specialVertex) + std::string(" Node]");
}
