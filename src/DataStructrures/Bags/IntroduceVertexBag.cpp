//
// Created by louis on 10/11/2021.
//

#include "IntroduceVertexBag.h"

DataStructures::IntroduceVertexBag::IntroduceVertexBag(
        int id, size_t size, DataStructures::BagContent vertices, NiceBag* child, DataStructures::VertexType introducedVertex)
        : IntroduceForgetVertexBagBase(id, size, std::move(vertices), child, DataStructures::BagType::IntroduceVertexBag, introducedVertex)
{}

DataStructures::VertexType DataStructures::IntroduceVertexBag::getIntroducedVertex() const
{
    return specialVertex;
}
