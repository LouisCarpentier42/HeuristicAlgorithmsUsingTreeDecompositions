//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
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
