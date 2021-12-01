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
        const NiceNode* child{nullptr};

    protected:
        IntroduceForgetNodeBase(int id, size_t size, BagContent bagContent, NiceNode* child, NodeType , VertexType specialVertex);

    public:
        [[nodiscard]] const NiceNode* getChild() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEFORGETNODEBASE_H
