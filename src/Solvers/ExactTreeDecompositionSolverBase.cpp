//
// Created by louis on 08/02/2022.
//

#include "ExactTreeDecompositionSolverBase.h"

int Solvers::ExactTreeDecompositionSolverBase::solve(
        DataStructures::Graph* graph,
        DataStructures::NiceTreeDecomposition* treeDecomposition)
{
    setProperties(graph);
    Solvers::ExactTreeDecompositionRankingMHV rankingRoot = solveAtNode(treeDecomposition->getRoot());
    return rankingRoot.getBestEvaluation();
}

Solvers::ExactTreeDecompositionRankingMHV Solvers::ExactTreeDecompositionSolverBase::solveAtNode(
        DataStructures::NiceNode* node,
        std::vector<ExactTreeDecompositionRankingMHV> rankingsChildren) const
{
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
        {
            return handleLeafNode(dynamic_cast<DataStructures::LeafNode*>(node));
        }
        case DataStructures::NodeType::IntroduceNode:
        {
            auto* introduceNode = dynamic_cast<DataStructures::IntroduceNode*>(node);
            if (rankingsChildren.empty())
            {
                return handleIntroduceNode(introduceNode,solveAtNode(introduceNode->getChild()));
            }
            else
            {
                return handleIntroduceNode(introduceNode, rankingsChildren[0]);
            }
        }
        case DataStructures::NodeType::ForgetNode:
        {
            auto* forgetNode = dynamic_cast<DataStructures::ForgetNode*>(node);
            if (rankingsChildren.empty())
            {
                return handleForgetNode(forgetNode, solveAtNode(forgetNode->getChild()));
            }
            else
            {
                return handleForgetNode(forgetNode, rankingsChildren[0]);
            }
        }
        case DataStructures::NodeType::JoinNode:
        {
            auto* joinNode = dynamic_cast<DataStructures::JoinNode*>(node);
            if (rankingsChildren.empty())
            {
                return handleJoinNode(joinNode, solveAtNode(joinNode->getLeftChild()), solveAtNode(joinNode->getRightChild()));
            }
            else
            {
                return handleJoinNode(joinNode, rankingsChildren[0], rankingsChildren[1]);
            }
        }
    }
}
