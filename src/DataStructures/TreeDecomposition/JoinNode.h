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
        NiceNode* leftChild;
        NiceNode* rightChild;

    public:
        JoinNode(int id, size_t size, BagContent bagContent, NiceNode* leftChild, NiceNode* rightChild);

        [[nodiscard]] NiceNode* getLeftChild();
        [[nodiscard]] NiceNode* getRightChild();

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JOINNODE_H
