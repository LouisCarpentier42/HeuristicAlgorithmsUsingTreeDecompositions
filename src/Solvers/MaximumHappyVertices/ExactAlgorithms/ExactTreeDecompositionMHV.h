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
#include "../../SolversUtility/ExactTreeDecompositionRanking.h"
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
        Solvers::ExactTreeDecompositionRanking handleLeafNode(
            DataStructures::LeafNode* node
        ) const override;
        Solvers::ExactTreeDecompositionRanking handleIntroduceNode(
            DataStructures::IntroduceNode* node,
            const Solvers::ExactTreeDecompositionRanking& rankingChild
        ) const override;
        Solvers::ExactTreeDecompositionRanking handleForgetNode(
            DataStructures::ForgetNode* node,
            const Solvers::ExactTreeDecompositionRanking& rankingChild
        ) const override;
        Solvers::ExactTreeDecompositionRanking handleJoinNode(
            DataStructures::JoinNode* node,
            const Solvers::ExactTreeDecompositionRanking& rankingLeftChild,
            const Solvers::ExactTreeDecompositionRanking& rankingRightChild
        ) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHV_H
