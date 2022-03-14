//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_FORGETNODE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_FORGETNODE_H

#include "../Graph/Graph.h"
#include "IntroduceForgetNodeBase.h"

namespace DataStructures
{
    class ForgetNode : public IntroduceForgetNodeBase
    {
    public:
        ForgetNode(int id, size_t size, BagContent bagContent, std::shared_ptr<NiceNode>& child, VertexType forgottenVertex);

        [[nodiscard]] DataStructures::VertexType getForgottenVertex() const;

        [[nodiscard]] std::string getTypeString() const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_FORGETNODE_H
