//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
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
        IntroduceNode(int id, size_t size, BagContent bagContent, std::shared_ptr<NiceNode>& child, VertexType introducedVertex);

        [[nodiscard]] DataStructures::VertexType getIntroducedVertex() const;

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCENODE_H
