//
// Created by louis on 10/11/2021.
//
#include "HeuristicTreeDecompositionSolver.h"
#include "../../DataStructures/Evaluator/BasicMHVEvaluator.h" // TODO remove

#include <iostream>

Solvers::HeuristicTreeDecompositionSolver::HeuristicTreeDecompositionSolver(
        size_t nbSolutionsToKeep,
        const DataStructures::Evaluator* evaluator,
        Solvers::LeafNodeHandler* leafNodeHandler,
        Solvers::IntroduceNodeHandler* introduceNodeHandler,
        Solvers::ForgetNodeHandler* forgetNodeHandler,
        Solvers::JoinNodeHandler* joinNodeHandler)
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
        DataStructures::Graph* graph,
        DataStructures::NiceTreeDecomposition* treeDecomposition) const
{
    std::cout << *treeDecomposition << "\n";
    leafNodeHandler->setInputInstanceProperties(graph);
    introduceNodeHandler->setInputInstanceProperties(graph);
    forgetNodeHandler->setInputInstanceProperties(graph);
    joinNodeHandler->setInputInstanceProperties(graph);

    solveAtNode(treeDecomposition->getRoot());

    treeDecomposition->getRoot()->getTable()->getBestEntry()->colourGraph(graph);
}

void Solvers::HeuristicTreeDecompositionSolver::solveAtNode(DataStructures::NiceNode* node) const
{
    node->getTable()->setCapacity(nbSolutionsToKeep);
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
            leafNodeHandler->handleLeafNode(dynamic_cast<DataStructures::LeafNode*>(node));
            break;
        case DataStructures::NodeType::IntroduceNode:
            introduceNodeHandler->handleIntroduceNode(dynamic_cast<DataStructures::IntroduceNode*>(node));
            break;
        case DataStructures::NodeType::ForgetNode:
            forgetNodeHandler->handleForgetVertexBag(dynamic_cast<DataStructures::ForgetNode*>(node));
            break;
        case DataStructures::NodeType::JoinNode:
            joinNodeHandler->handleJoinNode(dynamic_cast<DataStructures::JoinNode*>(node));
            break;
    }

    std::cout << "--- " << node->getId() << " ---\n";
    int count{1};
    DataStructures::BasicMHVEvaluator e{};
    for (DataStructures::TableEntry* entry : *node->getTable())
    {
        entry->colourGraph(leafNodeHandler->graph);
        std::cout << "E(" << count++ << "): " << entry->getEvaluation() << " " << e.evaluate(leafNodeHandler->graph) << " " << entry->getColourAssignments() << "\n";
        leafNodeHandler->graph->removeColours();
    }
    std::cout << "\n";
}


void Solvers::NodeHandler::setSolverProperties(
        const DataStructures::Evaluator* newEvaluator,
        const Solvers::HeuristicTreeDecompositionSolver* newSolver)
{
    if (this->evaluator == nullptr || this->solver == nullptr)
    {
        setEvaluator(newEvaluator);
        setSolver(newSolver);
    }
}

void Solvers::NodeHandler::setInputInstanceProperties(DataStructures::Graph* graphToSolve) // TODO set param const
{
    setGraph(graphToSolve);
}

void Solvers::NodeHandler::setEvaluator(const DataStructures::Evaluator* newEvaluator)
{
    this->evaluator = newEvaluator;
}

void Solvers::NodeHandler::setSolver(const Solvers::HeuristicTreeDecompositionSolver* newSolver)
{
    this->solver = newSolver;
}

void Solvers::NodeHandler::setGraph(DataStructures::Graph* graphToSolve) // TODO set param const
{
    this->graph = graphToSolve;
}


