//
// Created by louis on 08/02/2022.
//

#include "ExactTreeDecompositionSolverBase.h"

int Solvers::ExactTreeDecompositionSolverBase::solve(
        std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition)
{
    setProperties(graph);
    auto root = treeDecomposition->getRoot();
    Solvers::ExactTreeDecompositionRankingMHV rankingRoot = solveAtNode(root);

    std::shared_ptr<DataStructures::ColourAssignment> bestColouring = rankingRoot.getBestFullColouring();
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!graph->isPrecoloured(vertex))
            graph->setColour(vertex, bestColouring->getColour(vertex));
    }

    return rankingRoot.getBestEvaluation();
}

Solvers::ExactTreeDecompositionRankingMHV Solvers::ExactTreeDecompositionSolverBase::solveAtNode(
        std::shared_ptr<DataStructures::NiceNode>& node,
        const std::vector<ExactTreeDecompositionRankingMHV>& rankingsChildren) const
{
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
        {
            auto leafNode = std::dynamic_pointer_cast<DataStructures::LeafNode>(node);
            return handleLeafNode(leafNode);
        }
        case DataStructures::NodeType::IntroduceNode:
        {
            auto introduceNode = std::dynamic_pointer_cast<DataStructures::IntroduceNode>(node);
            if (rankingsChildren.empty())
            {
                auto child = introduceNode->getChild();
                auto rankingChild = solveAtNode(child);
                return handleIntroduceNode(introduceNode,rankingChild);
            }
            else
            {
                return handleIntroduceNode(introduceNode, rankingsChildren[0]);
            }
        }
        case DataStructures::NodeType::ForgetNode:
        {
            auto forgetNode = std::dynamic_pointer_cast<DataStructures::ForgetNode>(node);
            if (rankingsChildren.empty())
            {
                auto child = forgetNode->getChild();
                auto rankingChild = solveAtNode(child);
                return handleForgetNode(forgetNode, rankingChild);
            }
            else
            {
                return handleForgetNode(forgetNode, rankingsChildren[0]);
            }
        }
        case DataStructures::NodeType::JoinNode:
        {
            auto joinNode = std::dynamic_pointer_cast<DataStructures::JoinNode>(node);
            if (rankingsChildren.empty())
            {
                auto leftChild = joinNode->getLeftChild();
                auto rightChild = joinNode->getRightChild();
                auto rankingLeftChild = solveAtNode(leftChild);
                auto rankingRightChild = solveAtNode(rightChild);
                return handleJoinNode(joinNode, rankingLeftChild, rankingRightChild);
            }
            else
            {
                return handleJoinNode(joinNode, rankingsChildren[0], rankingsChildren[1]);
            }
        }
    }
}
