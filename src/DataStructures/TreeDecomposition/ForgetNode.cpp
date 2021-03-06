//
// Created by louis on 10/11/2021.
//

#include "ForgetNode.h"

DataStructures::ForgetNode::ForgetNode(
        int id, size_t size, DataStructures::BagContent bagContent, std::shared_ptr<NiceNode>& child, DataStructures::VertexType forgottenVertex)
    : IntroduceForgetNodeBase(id, size, std::move(bagContent), child, DataStructures::NodeType::ForgetNode, forgottenVertex)
{}

DataStructures::VertexType DataStructures::ForgetNode::getForgottenVertex() const
{
    return specialVertex;
}

std::string DataStructures::ForgetNode::getTypeString() const
{
    return std::string("[Forget Vertex ") + std::to_string(specialVertex) + std::string(" Node]");
}