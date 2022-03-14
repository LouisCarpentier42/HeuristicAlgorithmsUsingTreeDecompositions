//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NODE_H

#include "../Graph/Graph.h"

#include <iostream>
#include <set>
#include <memory>

namespace DataStructures
{
    using BagContent = std::set<VertexType>;

    class Node
    {
    protected:
        std::vector<std::shared_ptr<Node>> childVector;
    private:
        const int id{};
        const size_t bagSize{};
        const BagContent bagContent{};

    protected:
        Node(int id, size_t size, BagContent bagContent, std::vector<std::shared_ptr<Node>> childVector);

    public:
        [[nodiscard]] int getId() const;
        [[nodiscard]] size_t getBagSize() const;
        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] BagContent getBagContent() const;
        [[nodiscard]] bool isLeaf() const;
        [[nodiscard]] int getNbChildren() const;
        [[nodiscard]] int getHeight() const;

        [[nodiscard]] std::vector<std::shared_ptr<Node>>::const_iterator beginChildrenIterator() const;
        [[nodiscard]] std::vector<std::shared_ptr<Node>>::const_iterator endChildrenIterator() const;

    public:
        friend std::ostream& operator<<(std::ostream& out, const Node& node);
    private:
        std::ostream& prettyPrint(std::ostream& out, std::string& prefix) const;
        [[nodiscard]] virtual std::string getTypeString() const;

    public:

        // No public constructor, only a factory function,
        // so there's no way to have getptr return nullptr.
        [[nodiscard]] static std::shared_ptr<Node> create() {
            // Not using std::make_shared<Best> because the c'tor is private.
            return std::shared_ptr<Node>(new Node());
        }

    private:
        Node() = default;
    };
    std::ostream& operator<<(std::ostream& out, const Node& node);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NODE_H
