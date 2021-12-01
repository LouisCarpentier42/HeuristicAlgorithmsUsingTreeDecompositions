//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_LEAFNODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_LEAFNODE_H

#include "NiceNode.h"

namespace DataStructures
{
    class LeafNode : public NiceNode
    {
    public:
        explicit LeafNode(int id);

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_LEAFNODE_H
