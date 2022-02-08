//
// Created by louis on 08/02/2022.
//

#include "ExactTreeDecompositionSolverBase.h"

int Solvers::ExactTreeDecompositionSolverBase::solve(
        DataStructures::Graph* graph,
        DataStructures::NiceTreeDecomposition* treeDecomposition)
{
    setProperties(graph);
    Solvers::ExactTreeDecompositionRanking rankingRoot = solveAtNode(treeDecomposition->getRoot());
    return rankingRoot.getBestEvaluation();
}

Solvers::ExactTreeDecompositionRanking Solvers::ExactTreeDecompositionSolverBase::solveAtNode(DataStructures::NiceNode* node) const
{
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
            return handleLeafNode(dynamic_cast<DataStructures::LeafNode*>(node));
        case DataStructures::NodeType::IntroduceNode:
            return handleIntroduceNode(dynamic_cast<DataStructures::IntroduceNode*>(node));
        case DataStructures::NodeType::ForgetNode:
            return handleForgetVertexBag(dynamic_cast<DataStructures::ForgetNode*>(node));
        case DataStructures::NodeType::JoinNode:
            return handleJoinNode(dynamic_cast<DataStructures::JoinNode*>(node));
    }
}