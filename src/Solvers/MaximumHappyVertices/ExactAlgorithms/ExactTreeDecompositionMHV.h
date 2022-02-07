//
// Created by louis on 04/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHV_H

#include "../../../DataStructures/Graph/Graph.h"
#include "../../../DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "../../../DataStructures/TreeDecomposition/LeafNode.h"
#include "../../../DataStructures/TreeDecomposition/IntroduceNode.h"
#include "../../../DataStructures/TreeDecomposition/ForgetNode.h"
#include "../../../DataStructures/TreeDecomposition/JoinNode.h"
#include "ExactTreeDecompositionRanking.h"

#include <set>

namespace MaximumHappyVertices
{
    class ExactTreeDecompositionMHV
    {
    private:
        DataStructures::Graph* graph;
        std::set<DataStructures::VertexType> S{};

    public:
        [[nodiscard]] int solve(
            DataStructures::Graph* graph,
            DataStructures::NiceTreeDecomposition* treeDecomposition
        );
        ExactTreeDecompositionRanking solveAtNode(DataStructures::NiceNode* node) const;

        void setProperties(DataStructures::Graph* graph);

    private:
        ExactTreeDecompositionRanking handleLeafNode(DataStructures::LeafNode* node) const;
        ExactTreeDecompositionRanking handleIntroduceNode(DataStructures::IntroduceNode* node) const;
        ExactTreeDecompositionRanking handleForgetVertexBag(DataStructures::ForgetNode* node) const;
        ExactTreeDecompositionRanking handleJoinNode(DataStructures::JoinNode* node) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHV_H
