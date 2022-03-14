//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICENODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICENODE_H

#include "Node.h"
#include "../DynamicProgramming/DynamicProgrammingTable.h"

namespace DataStructures
{
    enum class NodeType {
        LeafNode,
        ForgetNode,
        IntroduceNode,
        JoinNode
    };

    class NiceNode : public Node
    {
    private:
        std::unique_ptr<DynamicProgrammingTable> table{new DynamicProgrammingTable{0}};
        const NodeType bagType;

    protected:
        NiceNode(int id, size_t size, BagContent bagContent, std::vector<std::shared_ptr<Node>> childVector, NodeType bagType);

    public:
        [[nodiscard]] NodeType getNodeType() const;
        [[nodiscard]] DynamicProgrammingTable& getTable();
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICENODE_H
