//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINNODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINNODE_H

#include "NiceNode.h"

namespace DataStructures
{
    class JoinNode : public NiceNode
    {
    private:
        std::shared_ptr<NiceNode> leftChild;
        std::shared_ptr<NiceNode> rightChild;

    public:
        JoinNode(int id, size_t size, BagContent bagContent, std::shared_ptr<NiceNode>& leftChild, std::shared_ptr<NiceNode>& rightChild);

        [[nodiscard]] std::shared_ptr<NiceNode> getLeftChild();
        [[nodiscard]] std::shared_ptr<NiceNode> getRightChild();

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINNODE_H
