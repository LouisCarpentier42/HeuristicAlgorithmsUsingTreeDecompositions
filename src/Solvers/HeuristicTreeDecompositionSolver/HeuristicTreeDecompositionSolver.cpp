//
// Created by louis on 10/11/2021.
//
#include "HeuristicTreeDecompositionSolver.h"

Solvers::HeuristicTreeDecompositionSolver::HeuristicTreeDecompositionSolver(
        size_t nbSolutionsToKeep,
        const DataStructures::ColouringEvaluator* evaluator,
        Solvers::LeafNodeHandler* leafNodeHandler,
        Solvers::IntroduceNodeHandler* introduceNodeHandler,
        Solvers::ForgetNodeHandler* forgetNodeHandler,
        Solvers::JoinNodeHandler* joinNodeHandler)
    : leafNodeHandler{leafNodeHandler},
      introduceNodeHandler{introduceNodeHandler},
      forgetNodeHandler{forgetNodeHandler},
      joinNodeHandler{joinNodeHandler}
{
    this->leafNodeHandler->setSolverProperties(nbSolutionsToKeep, evaluator, this);
    this->introduceNodeHandler->setSolverProperties(nbSolutionsToKeep, evaluator, this);
    this->forgetNodeHandler->setSolverProperties(nbSolutionsToKeep, evaluator, this);
    this->joinNodeHandler->setSolverProperties(nbSolutionsToKeep, evaluator, this);
}

DataStructures::Colouring* Solvers::HeuristicTreeDecompositionSolver::solve(
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring,
        const DataStructures::NiceTreeDecomposition* treeDecomposition) const
{
    leafNodeHandler->setInputInstanceProperties(graph, colouring);
    introduceNodeHandler->setInputInstanceProperties(graph, colouring);
    forgetNodeHandler->setInputInstanceProperties(graph, colouring);
    joinNodeHandler->setInputInstanceProperties(graph, colouring);
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


void Solvers::NodeHandler::setSolverProperties(
        size_t newNbSolutionsToKeep,
        const DataStructures::ColouringEvaluator* newEvaluator,
        const Solvers::HeuristicTreeDecompositionSolver* newSolver)
{
    if (this->evaluator == nullptr || this->solver == nullptr)
    {
        setNbSolutionsToKeep(newNbSolutionsToKeep);
        setEvaluator(newEvaluator);
        setSolver(newSolver);
    }
}

void Solvers::NodeHandler::setInputInstanceProperties(
        const DataStructures::Graph* graphToSolve,
        const DataStructures::Colouring* colouringToSolve)
{
    setGraph(graphToSolve);
    setColouring(colouringToSolve);
}

DataStructures::ColouringQueue Solvers::NodeHandler::createEmptyColouringQueue() const
{
    return DataStructures::ColouringQueue{nbSolutionsToKeep, evaluator, graph};
}

void Solvers::NodeHandler::setNbSolutionsToKeep(size_t newNbSolutionsToKeep)
{
    this->nbSolutionsToKeep = newNbSolutionsToKeep;
}

void Solvers::NodeHandler::setEvaluator(const DataStructures::ColouringEvaluator* newEvaluator)
{
    this->evaluator = newEvaluator;
}

void Solvers::NodeHandler::setSolver(const Solvers::HeuristicTreeDecompositionSolver* newSolver)
{
    this->solver = newSolver;
}

void Solvers::NodeHandler::setGraph(const DataStructures::Graph* graphToSolve)
{
    this->graph = graphToSolve;
}

void Solvers::NodeHandler::setColouring(const DataStructures::Colouring* colouringToSolve)
{
    this->colouring = colouringToSolve;
}

