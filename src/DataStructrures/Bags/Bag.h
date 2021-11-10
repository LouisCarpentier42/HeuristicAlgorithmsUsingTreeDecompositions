//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H

#include "../Graph.h"

#include <iostream>
#include <vector>

namespace DataStructures
{
    class Bag;
    using BagContent = std::vector<DataStructures::VertexType>;
    using ChildVector = std::vector<Bag*>;

    class Bag
    {
    protected:
        std::vector<Bag*> childVector;
    private:
        const int id;
        const size_t bagSize;
        const DataStructures::BagContent vertices;
        Bag* parent{nullptr};


    protected:
        Bag(int id, size_t size, DataStructures::BagContent vertices, ChildVector childVector);

    public:
        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] const Bag* getParent() const;
        [[nodiscard]] bool isLeaf() const;

        [[nodiscard]] std::vector<Bag*>::const_iterator beginChildrenIterator() const;
        [[nodiscard]] std::vector<Bag*>::const_iterator endChildrenIterator() const;

    protected:
        void setParent(Bag* newParent);

    public:
        friend std::ostream& operator<<(std::ostream& out, const Bag& bag);
    private:
        std::ostream& prettyPrint(std::ostream& out, std::string& prefix) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H
