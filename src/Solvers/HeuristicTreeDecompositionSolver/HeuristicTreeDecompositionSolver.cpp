//
// Created by louis on 10/11/2021.
//
#include "HeuristicTreeDecompositionSolver.h"

Solvers::HeuristicTreeDecompositionSolver::HeuristicTreeDecompositionSolver(
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* partialColouring,
        const DataStructures::ColouringEvaluator* evaluator,
        size_t nbSolutionsToKeep,
        const DataStructures::NiceTreeDecomposition* treeDecomposition,
        LeafNodeHandler* leafNodeHandler,
        IntroduceNodeHandler* introduceNodeHandler,
        ForgetNodeHandler* forgetNodeHandler,
        JoinNodeHandler* joinNodeHandler)
    : SolverBase(graph, partialColouring, evaluator),
      nbSolutionsToKeep{nbSolutionsToKeep},
      treeDecomposition{treeDecomposition},
      leafNodeHandler{leafNodeHandler},
      introduceNodeHandler{introduceNodeHandler},
      forgetNodeHandler{forgetNodeHandler},
      joinNodeHandler{joinNodeHandler}
{
    leafNodeHandler->setSolver(this);
    introduceNodeHandler->setSolver(this);
    forgetNodeHandler->setSolver(this);
    joinNodeHandler->setSolver(this);
}

DataStructures::MutableColouring* Solvers::HeuristicTreeDecompositionSolver::solve() const
{
    DataStructures::ColouringQueue rootColourings = solveAtNode(treeDecomposition->getRoot());
    return rootColourings.retrieveBestColouring();
}

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::solveAtNode(const DataStructures::NiceNode* node) const
{
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
            return leafNodeHandler->handleLeafNode(dynamic_cast<const DataStructures::LeafNode*>(node));
        case DataStructures::NodeType::IntroduceNode:
            return introduceNodeHandler->handleIntroduceNode(dynamic_cast<const DataStructures::IntroduceNode*>(node));
        case DataStructures::NodeType::ForgetNode:
            return forgetNodeHandler->handleForgetVertexBag(dynamic_cast<const DataStructures::ForgetNode*>(node));
        case DataStructures::NodeType::JoinNode:
            return joinNodeHandler->handleJoinNode(dynamic_cast<const DataStructures::JoinNode*>(node));
    }
}

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::createEmptyColouringQueue() const
{
    return DataStructures::ColouringQueue{nbSolutionsToKeep, evaluator};
}

void Solvers::NodeHandler::setSolver(Solvers::HeuristicTreeDecompositionSolver* newSolver)
{
    if (!solver)
        solver = newSolver;
}
