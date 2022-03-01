//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NODE_H

#include "../Graph/Graph.h"

#include <iostream>
#include <set>

namespace DataStructures
{
    using BagContent = std::set<DataStructures::VertexType>;

    class Node
    {
    protected:
        std::vector<Node*> childVector;
    private:
        const int id;
        const size_t bagSize;
        const DataStructures::BagContent bagContent;
        Node* parent{nullptr};

    protected:
        Node(int id, size_t size, DataStructures::BagContent bagContent, std::vector<Node*> childVector);

    public:
        [[nodiscard]] int getId() const;
        [[nodiscard]] size_t getBagSize() const;
        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] BagContent getBagContent() const;
        [[nodiscard]] const Node* getParent() const;
        [[nodiscard]] bool isLeaf() const;
        [[nodiscard]] int getNbChildren() const;
        [[nodiscard]] int getHeight() const;

        [[nodiscard]] std::vector<Node*>::const_iterator beginChildrenIterator() const;
        [[nodiscard]] std::vector<Node*>::const_iterator endChildrenIterator() const;

    protected:
        void setParent(Node* newParent);

    public:
        friend std::ostream& operator<<(std::ostream& out, const Node& node);
    private:
        std::ostream& prettyPrint(std::ostream& out, std::string& prefix) const;
        [[nodiscard]] virtual std::string getTypeString() const;
    };
    std::ostream& operator<<(std::ostream& out, const Node& node);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NODE_H
