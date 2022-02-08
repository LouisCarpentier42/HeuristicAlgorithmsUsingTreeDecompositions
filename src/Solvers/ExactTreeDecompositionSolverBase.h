//
// Created by louis on 08/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONSOLVERBASE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONSOLVERBASE_H

#include "../DataStructures/Graph/Graph.h"
#include "ExactTreeDecompositionUtility/ExactTreeDecompositionRanking.h"
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
        ExactTreeDecompositionRanking solveAtNode(DataStructures::NiceNode* node) const;
        virtual void setProperties(DataStructures::Graph* graph) = 0;

    private:
        virtual Solvers::ExactTreeDecompositionRanking handleLeafNode(DataStructures::LeafNode* node) const = 0;
        virtual Solvers::ExactTreeDecompositionRanking handleIntroduceNode(DataStructures::IntroduceNode* node) const = 0;
        virtual Solvers::ExactTreeDecompositionRanking handleForgetVertexBag(DataStructures::ForgetNode* node) const = 0;
        virtual Solvers::ExactTreeDecompositionRanking handleJoinNode(DataStructures::JoinNode* node) const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONSOLVERBASE_H
