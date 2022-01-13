//
// Created by louis on 03/09/2021.
//

#include "Node.h"

DataStructures::Node::Node(int id, size_t size, BagContent bagContent, std::vector<Node*> childVector)
    : id{id}, bagSize{size}, bagContent{std::move(bagContent)}, childVector{std::move(childVector)}
{
    for (Node* child : this->childVector)
        child->setParent(this);
}

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

const DataStructures::Node* DataStructures::Node::getParent() const
{
    return parent;
}

void DataStructures::Node::setParent(DataStructures::Node* newParent)
{
    this->parent = newParent;
}

bool DataStructures::Node::isLeaf() const
{
    return childVector.empty();
}

int DataStructures::Node::getNbChildren() const
{
    return childVector.size();
}

std::vector<DataStructures::Node*>::const_iterator DataStructures::Node::beginChildrenIterator() const
{
    return childVector.begin();
}

std::vector<DataStructures::Node*>::const_iterator DataStructures::Node::endChildrenIterator() const
{
    return childVector.end();
}


std::ostream& DataStructures::operator<<(std::ostream& out, const DataStructures::Node& node)
{
    std::string prefix{};
    return node.prettyPrint(out, prefix);
}

std::ostream& DataStructures::Node::prettyPrint(std::ostream& out, std::string& prefix) const
{
    out << "b(" << id << "): " << "{";
    if (bagSize > 0)
    {
        for (int i = 0; i < bagSize - 1; i++)
            out << bagContent[i] << ", ";
        out << bagContent[bagSize - 1];
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
