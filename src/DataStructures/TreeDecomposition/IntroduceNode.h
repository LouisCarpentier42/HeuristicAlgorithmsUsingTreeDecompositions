//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCENODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCENODE_H

#include "../Graph/Graph.h"
#include "IntroduceForgetNodeBase.h"

namespace DataStructures
{
    class IntroduceNode : public IntroduceForgetNodeBase
    {
    public:
        IntroduceNode(int id, size_t size, BagContent bagContent, NiceNode* child, VertexType introducedVertex);

        [[nodiscard]] DataStructures::VertexType getIntroducedVertex() const;

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCENODE_H
