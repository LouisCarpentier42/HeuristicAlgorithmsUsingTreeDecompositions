//
// Created by louis on 03/09/2021.
//

#include "Bag.h"

namespace DataStructures
{
    Bag::Bag(int id, size_t size, std::vector<int> vertices)
        : id{id}, bagSize{size}, vertices{std::move(vertices)}
    {}

    Bag* Bag::getParent() const
    {
        return parent;
    }

    void Bag::addChild(Bag* child)
    {
        children.push_back(child);
        child->parent = this;
    }

    bool Bag::isEmpty() const
    {
        return vertices.empty();
    }

    std::ostream& operator<<(std::ostream& out, const Bag& bag)
    {
        std::string prefix{};
        return bag.prettyPrint(out, prefix);
    }

    std::ostream& Bag::prettyPrint(std::ostream& out, std::string& prefix) const
    {
        out << "b(" << id << "): {";
        if (bagSize > 0)
        {
            for (int i = 0; i < bagSize - 1; i++)
                out << vertices[i] << ", ";
            out << vertices[bagSize-1];
        }
        out << "}\n";

        if (!children.empty())
        {
            std::string standardPrefix{prefix + "│   "};
            std::string prefixLast{prefix + "    "};
            for (int i = 0; i < children.size()-1; i++) {
                out << prefix << "├── ";
                children[i]->prettyPrint(out, standardPrefix);
            }
            out << prefix << "└── ";
            children[children.size()-1]->prettyPrint(out, prefixLast);
        }
       return out;
    }
}
