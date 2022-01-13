//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEFORGETNODEBASE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEFORGETNODEBASE_H

#include "NiceNode.h"

namespace DataStructures
{
    class IntroduceForgetNodeBase : public NiceNode
    {
    protected:
        const DataStructures::VertexType specialVertex;
    private:
        NiceNode* child{nullptr};

    protected:
        IntroduceForgetNodeBase(int id, size_t size, BagContent bagContent, NiceNode* child, NodeType , VertexType specialVertex);

    public:
        [[nodiscard]] NiceNode* getChild();
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEFORGETNODEBASE_H
