//
// Created by louis on 03/09/2021.
//

#include "Bag.h"

DataStructures::Bag::Bag(int id, size_t size, BagContent vertices, ChildVector childVector)
    : id{id}, bagSize{size}, vertices{std::move(vertices)}, childVector{std::move(childVector)}
{
    for (Bag* child : this->childVector)
        child->setParent(this);
}

bool DataStructures::Bag::isEmpty() const
{
    return vertices.empty();
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
    out << "b(" << id << "): {";
    if (bagSize > 0)
    {
        for (int i = 0; i < bagSize - 1; i++)
            out << vertices[i] << ", ";
        out << vertices[bagSize-1];
    }
    out << "}\n";

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
