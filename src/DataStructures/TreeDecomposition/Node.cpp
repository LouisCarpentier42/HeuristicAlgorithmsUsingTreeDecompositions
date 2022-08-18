//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "Node.h"

DataStructures::Node::Node(int id, size_t size, BagContent bagContent, std::vector<std::shared_ptr<Node>> childVector)
    : id{id}, bagSize{size}, bagContent{std::move(bagContent)}, childVector{std::move(childVector)}
{}

int DataStructures::Node::getId() const
{
    return id;
}

size_t DataStructures::Node::getBagSize() const
{
    return bagSize;
}

bool DataStructures::Node::isEmpty() const
{
    return bagContent.empty();
}

DataStructures::BagContent DataStructures::Node::getBagContent() const
{
    return bagContent;
}

bool DataStructures::Node::isLeaf() const
{
    return childVector.empty();
}

int DataStructures::Node::getNbChildren() const
{
    return childVector.size();
}

int DataStructures::Node::getHeight() const
{
    if (isLeaf()) return 0;

    int height{0};
    for (const std::shared_ptr<Node>& child : childVector)
    {
        int heightChild{child->getHeight()};
        if (heightChild > height)
            height = heightChild;
    }
    return height + 1;
}

int DataStructures::Node::getNbNodes() const
{
    if (isLeaf()) return 1;

    int nbNodes{1};
    for (const std::shared_ptr<Node>& child : childVector)
    {
        nbNodes += child->getNbNodes();
    }
    return nbNodes;
}


std::vector<std::shared_ptr<DataStructures::Node>>::const_iterator DataStructures::Node::beginChildrenIterator() const
{
    return childVector.begin();
}

std::vector<std::shared_ptr<DataStructures::Node>>::const_iterator DataStructures::Node::endChildrenIterator() const
{
    return childVector.end();
}


std::ostream& DataStructures::operator<<(std::ostream& out, const Node& node)
{
    std::string prefix{};
    return node.prettyPrint(out, prefix);
}

std::ostream& DataStructures::Node::prettyPrint(std::ostream& out, std::string& prefix) const
{
    out << "b(" << id << "): " << "{";
    if (bagSize > 0)
    {
        for (auto value : bagContent)
            out << value << ",";
    }
    out << "} " << getTypeString() << "\n";

    if (beginChildrenIterator() != endChildrenIterator())
    {
        std::string standardPrefix{prefix + "│   "};
        std::string prefixLast{prefix + "    "};
        auto it = beginChildrenIterator();
        while (it != endChildrenIterator() - 1) {
            out << prefix << "├── ";
            (*it++)->prettyPrint(out, standardPrefix);
        }
        out << prefix << "└── ";
        (*it)->prettyPrint(out, prefixLast);
    }
   return out;
}

std::string DataStructures::Node::getTypeString() const
{
    return "";
}
