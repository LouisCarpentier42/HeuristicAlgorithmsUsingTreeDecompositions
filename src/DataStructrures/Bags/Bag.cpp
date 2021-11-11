//
// Created by louis on 03/09/2021.
//

#include "Bag.h"

DataStructures::Bag::Bag(int id, size_t size, BagContent bagContent, ChildVector childVector)
    : id{id}, bagSize{size}, bagContent{std::move(bagContent)}, childVector{std::move(childVector)}
{
    for (Bag* child : this->childVector)
        child->setParent(this);
}

int DataStructures::Bag::getId() const
{
    return id;
}

size_t DataStructures::Bag::getBagSize() const
{
    return bagSize;
}

bool DataStructures::Bag::isEmpty() const
{
    return bagContent.empty();
}

DataStructures::BagContent DataStructures::Bag::getBagContent() const
{
    return bagContent;
}

const DataStructures::Bag* DataStructures::Bag::getParent() const
{
    return parent;
}

void DataStructures::Bag::setParent(DataStructures::Bag* newParent)
{
    this->parent = newParent;
}

bool DataStructures::Bag::isLeaf() const
{
    return childVector.empty();
}

int DataStructures::Bag::getNbChildren() const
{
    return childVector.size();
}

std::vector<DataStructures::Bag*>::const_iterator DataStructures::Bag::beginChildrenIterator() const
{
    return childVector.begin();
}

std::vector<DataStructures::Bag*>::const_iterator DataStructures::Bag::endChildrenIterator() const
{
    return childVector.end();
}




std::ostream& DataStructures::operator<<(std::ostream& out, const DataStructures::Bag& bag)
{
    std::string prefix{};
    return bag.prettyPrint(out, prefix);
}

std::ostream& DataStructures::Bag::prettyPrint(std::ostream& out, std::string& prefix) const
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

std::string DataStructures::Bag::getTypeString() const
{
    return "";
}
