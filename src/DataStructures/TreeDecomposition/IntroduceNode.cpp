//
// Created by louis on 10/11/2021.
//

#include "IntroduceNode.h"

DataStructures::IntroduceNode::IntroduceNode(
        int id, size_t size, DataStructures::BagContent bagContent, std::shared_ptr<NiceNode>& child, DataStructures::VertexType introducedVertex)
    : IntroduceForgetNodeBase(id, size, std::move(bagContent), child, DataStructures::NodeType::IntroduceNode, introducedVertex)
{}

DataStructures::VertexType DataStructures::IntroduceNode::getIntroducedVertex() const
{
    return specialVertex;
}

std::string DataStructures::IntroduceNode::getTypeString() const
{
    return std::string("[Introduce Vertex ") + std::to_string(specialVertex) + std::string(" Node]");
}
