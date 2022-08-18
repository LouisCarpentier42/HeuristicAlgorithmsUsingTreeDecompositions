//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_STANDARDNODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_STANDARDNODE_H

#include "Node.h"

namespace DataStructures
{
    class StandardNode : public Node
    {
    public:
        StandardNode(int id, size_t size, BagContent bagContent);

        void addChild(std::shared_ptr<StandardNode>& child);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_STANDARDNODE_H
