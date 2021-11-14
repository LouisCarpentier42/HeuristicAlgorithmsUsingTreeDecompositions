//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H

#include "../Graph/Graph.h"

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
        const DataStructures::BagContent bagContent;
        Bag* parent{nullptr};


    protected:
        Bag(int id, size_t size, DataStructures::BagContent bagContent, ChildVector childVector);

    public:
        [[nodiscard]] int getId() const;
        [[nodiscard]] size_t getBagSize() const;
        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] BagContent getBagContent() const;
        [[nodiscard]] const Bag* getParent() const;
        [[nodiscard]] bool isLeaf() const;
        [[nodiscard]] int getNbChildren() const;

        [[nodiscard]] std::vector<Bag*>::const_iterator beginChildrenIterator() const;
        [[nodiscard]] std::vector<Bag*>::const_iterator endChildrenIterator() const;

    protected:
        void setParent(Bag* newParent);

    public:
        friend std::ostream& operator<<(std::ostream& out, const Bag& bag);
    private:
        std::ostream& prettyPrint(std::ostream& out, std::string& prefix) const;
        [[nodiscard]] virtual std::string getTypeString() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H
