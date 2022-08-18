//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "HeuristicTreeDecompositionSolver.h"

Solvers::HeuristicTreeDecompositionSolver::HeuristicTreeDecompositionSolver(
        size_t nbSolutionsToKeep,
        std::shared_ptr<DataStructures::Evaluator> evaluator,
        std::shared_ptr<LeafNodeHandler>& leafNodeHandler,
        std::shared_ptr<IntroduceNodeHandler>& introduceNodeHandler,
        std::shared_ptr<ForgetNodeHandler>& forgetNodeHandler,
        std::shared_ptr<JoinNodeHandler>& joinNodeHandler)
    : nbSolutionsToKeep{nbSolutionsToKeep},
      leafNodeHandler{leafNodeHandler},
      introduceNodeHandler{introduceNodeHandler},
      forgetNodeHandler{forgetNodeHandler},
      joinNodeHandler{joinNodeHandler}
{
    this->leafNodeHandler->setSolverProperties(evaluator, this);
    this->introduceNodeHandler->setSolverProperties(evaluator, this);
    this->forgetNodeHandler->setSolverProperties(evaluator, this);
    this->joinNodeHandler->setSolverProperties(evaluator, this);
}

void Solvers::HeuristicTreeDecompositionSolver::solve(
        std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition) const
{
    leafNodeHandler->setInputInstanceProperties(graph);
    introduceNodeHandler->setInputInstanceProperties(graph);
    forgetNodeHandler->setInputInstanceProperties(graph);
    joinNodeHandler->setInputInstanceProperties(graph);

    std::shared_ptr<DataStructures::NiceNode> root = treeDecomposition->getRoot();
    solveAtNode(root);

    treeDecomposition->getRoot()->getTable().getBestEntry()->colourGraph(graph);
}

void Solvers::HeuristicTreeDecompositionSolver::solveAtNode(std::shared_ptr<DataStructures::NiceNode>& node) const
{
    node->getTable().setCapacity(nbSolutionsToKeep);
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
        {
            auto leafNode = std::dynamic_pointer_cast<DataStructures::LeafNode>(node);
            leafNodeHandler->handleLeafNode(leafNode);
            break;
        }
        case DataStructures::NodeType::IntroduceNode:
        {
            auto introduceNode = std::dynamic_pointer_cast<DataStructures::IntroduceNode>(node);
            introduceNodeHandler->handleIntroduceNode(introduceNode);
            break;
        }
        case DataStructures::NodeType::ForgetNode:
        {
            auto forgetNode = std::dynamic_pointer_cast<DataStructures::ForgetNode>(node);
            forgetNodeHandler->handleForgetVertexBag(forgetNode);
            break;
        }
        case DataStructures::NodeType::JoinNode:
        {
            auto joinNode = std::dynamic_pointer_cast<DataStructures::JoinNode>(node);
            joinNodeHandler->handleJoinNode(joinNode);
            break;
        }
    }
}

void Solvers::NodeHandler::setSolverProperties(
        std::shared_ptr<DataStructures::Evaluator>& newEvaluator,
        HeuristicTreeDecompositionSolver* newSolver)
{
    if (this->evaluator == nullptr || this->solver == nullptr)
    {
        setEvaluator(newEvaluator);
        setSolver(newSolver);
    }
}

void Solvers::NodeHandler::setInputInstanceProperties(std::shared_ptr<DataStructures::Graph>& graphToSolve)
{
    setGraph(graphToSolve);
}

void Solvers::NodeHandler::setEvaluator(std::shared_ptr<DataStructures::Evaluator>& newEvaluator)
{
    this->evaluator = newEvaluator;
}

void Solvers::NodeHandler::setSolver(HeuristicTreeDecompositionSolver* newSolver)
{
    this->solver = newSolver;
}

void Solvers::NodeHandler::setGraph(std::shared_ptr<DataStructures::Graph>& graphToSolve)
{
    this->graph = graphToSolve;
}


