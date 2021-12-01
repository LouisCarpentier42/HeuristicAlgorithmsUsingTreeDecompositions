//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINNODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINNODE_H

#include "NiceNode.h"

namespace DataStructures
{
    class JoinNode : public NiceNode
    {
    private:
        const NiceNode* leftChild;
        const NiceNode* rightChild;

    public:
        JoinNode(int id, size_t size, BagContent bagContent, NiceNode* leftChild, NiceNode* rightChild);

        [[nodiscard]] const NiceNode* getLeftChild() const;
        [[nodiscard]] const NiceNode* getRightChild() const;

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINNODE_H
