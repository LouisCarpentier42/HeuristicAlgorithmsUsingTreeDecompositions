//
// Created by louis on 03/09/2021.
//

#include "Bag.h"
namespace TreeDecomposition {
    Bag::Bag(int id, std::vector<int> vertices)
    : id{id}, size{vertices.size()}, vertices{std::move(vertices)}
    {}

    void Bag::addChild(Bag* child)
    {
        children.push_back(child);
    }

    std::ostream& operator<<(std::ostream& out, const Bag& bag)
    {
        out << "b " << bag.id;
        for(int vertex : bag.vertices)
        {
            out << ' ' << vertex;
        }
        out << '\n';
        for (Bag *child : bag.children)
        {
            out << bag.id << ' ' << child->id << '\n';
            out << *child;
        }
        return out;
    }
}
