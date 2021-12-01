//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICENODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICENODE_H

#include "Node.h"

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
        const NodeType bagType;

    protected:
        NiceNode(int id, size_t size, BagContent bagContent, ChildVector childVector, NodeType bagType);

    public:
        [[nodiscard]] NodeType getNodeType() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_NICENODE_H
