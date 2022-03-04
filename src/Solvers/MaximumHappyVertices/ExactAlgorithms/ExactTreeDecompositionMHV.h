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
#include "../ExactTreeDecompositionRankingMHV.h"
#include "../../ExactTreeDecompositionSolverBase.h"

#include <set>

namespace MaximumHappyVertices
{
    class ExactTreeDecompositionMHV : public Solvers::ExactTreeDecompositionSolverBase
    {
    private:
        DataStructures::Graph* graph;
        std::set<DataStructures::VertexType> S{};

    public:
        void setProperties(DataStructures::Graph* graph) override;

    private:
        Solvers::ExactTreeDecompositionRankingMHV handleLeafNode(
            DataStructures::LeafNode* node
        ) const override;
        Solvers::ExactTreeDecompositionRankingMHV handleIntroduceNode(
            DataStructures::IntroduceNode* node,
            const Solvers::ExactTreeDecompositionRankingMHV& rankingChild
        ) const override;
        Solvers::ExactTreeDecompositionRankingMHV handleForgetNode(
            DataStructures::ForgetNode* node,
            const Solvers::ExactTreeDecompositionRankingMHV& rankingChild
        ) const override;
        Solvers::ExactTreeDecompositionRankingMHV handleJoinNode(
            DataStructures::JoinNode* node,
            const Solvers::ExactTreeDecompositionRankingMHV& rankingLeftChild,
            const Solvers::ExactTreeDecompositionRankingMHV& rankingRightChild
        ) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHV_H
