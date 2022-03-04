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
            DataStructures::Graph* graph,
            DataStructures::NiceTreeDecomposition* treeDecomposition
        );
        ExactTreeDecompositionRankingMHV solveAtNode(
            DataStructures::NiceNode* node,
            std::vector<ExactTreeDecompositionRankingMHV> rankingsChildren = {}
        ) const;
        virtual void setProperties(DataStructures::Graph* graph) = 0;

    private:
        virtual Solvers::ExactTreeDecompositionRankingMHV handleLeafNode(
            DataStructures::LeafNode* node
        ) const = 0;
        virtual Solvers::ExactTreeDecompositionRankingMHV handleIntroduceNode(
            DataStructures::IntroduceNode* node,
            const ExactTreeDecompositionRankingMHV& rankingChild
        ) const = 0;
        virtual Solvers::ExactTreeDecompositionRankingMHV handleForgetNode(
            DataStructures::ForgetNode* node,
            const ExactTreeDecompositionRankingMHV& rankingChild
        ) const = 0;
        virtual Solvers::ExactTreeDecompositionRankingMHV handleJoinNode(
            DataStructures::JoinNode* node,
            const ExactTreeDecompositionRankingMHV& rankingLeftChild,
            const ExactTreeDecompositionRankingMHV& rankingRightChild
        ) const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONSOLVERBASE_H
