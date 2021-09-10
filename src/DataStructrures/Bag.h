//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H

#include <iostream>
#include <vector>

namespace DataStructures
{
    class Bag
    {
    private:
        const int id;
        size_t bagSize;
        std::vector<int> vertices;
        Bag* parent{nullptr};
        std::vector<Bag*> children{};

    public:
        Bag(int id, size_t size, std::vector<int> vertices);

        Bag* getParent() const;

        void addChild(Bag* child);
        bool isEmpty() const;

    private:
        std::ostream& prettyPrint(std::ostream& out, std::string& prefix) const;
        friend std::ostream& operator<<(std::ostream& out, const Bag& bag);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H
