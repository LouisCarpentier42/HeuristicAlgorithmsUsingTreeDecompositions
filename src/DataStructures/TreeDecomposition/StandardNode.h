//
// Created by louis on 10/11/2021.
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

        void addChild(StandardNode* child);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_STANDARDNODE_H
