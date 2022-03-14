//
// Created by louis on 08/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONSOLVERBASE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONSOLVERBASE_H

#include "../DataStructures/Graph/Graph.h"
#include "MaximumHappyVertices/ExactTreeDecompositionRankingMHV.h"
#include "../DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "../DataStructures/TreeDecomposition/LeafNode.h"
#include "../DataStructures/TreeDecomposition/IntroduceNode.h"
#include "../DataStructures/TreeDecomposition/ForgetNode.h"
#include "../DataStructures/TreeDecomposition/JoinNode.h"

namespace Solvers
{
    class ExactTreeDecompositionSolverBase
    {
    public:
        [[nodiscard]] int solve(
            std::shared_ptr<DataStructures::Graph>& graph,
            std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition
        );
        ExactTreeDecompositionRankingMHV solveAtNode(
            std::shared_ptr<DataStructures::NiceNode>& node,
            const std::vector<ExactTreeDecompositionRankingMHV>& rankingsChildren = {}
        ) const;
        virtual void setProperties(std::shared_ptr<DataStructures::Graph>& graph) = 0;

    private:
        virtual Solvers::ExactTreeDecompositionRankingMHV handleLeafNode(
            std::shared_ptr<DataStructures::LeafNode>& node
        ) const = 0;
        virtual Solvers::ExactTreeDecompositionRankingMHV handleIntroduceNode(
                std::shared_ptr<DataStructures::IntroduceNode>& node,
            const ExactTreeDecompositionRankingMHV& rankingChild
        ) const = 0;
        virtual Solvers::ExactTreeDecompositionRankingMHV handleForgetNode(
            std::shared_ptr<DataStructures::ForgetNode>& node,
            const ExactTreeDecompositionRankingMHV& rankingChild
        ) const = 0;
        virtual Solvers::ExactTreeDecompositionRankingMHV handleJoinNode(
            std::shared_ptr<DataStructures::JoinNode>& node,
            const ExactTreeDecompositionRankingMHV& rankingLeftChild,
            const ExactTreeDecompositionRankingMHV& rankingRightChild
        ) const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONSOLVERBASE_H
