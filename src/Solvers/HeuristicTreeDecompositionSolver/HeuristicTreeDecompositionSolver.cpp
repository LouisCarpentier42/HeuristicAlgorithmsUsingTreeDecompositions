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
        LeafBagHandler* leafBagHandler,
        IntroduceVertexBagHandler* introduceVertexBagHandler,
        ForgetVertexBagHandler* forgetVertexBagHandler,
        JoinBagHandler* joinBagHandler)
    : SolverBase(graph, partialColouring, evaluator),
      nbSolutionsToKeep{nbSolutionsToKeep},
      treeDecomposition{treeDecomposition},
      leafBagHandler{leafBagHandler},
      introduceVertexBagHandler{introduceVertexBagHandler},
      forgetVertexBagHandler{forgetVertexBagHandler},
      joinBagHandler{joinBagHandler}
{
    leafBagHandler->setSolver(this);
    introduceVertexBagHandler->setSolver(this);
    forgetVertexBagHandler->setSolver(this);
    joinBagHandler->setSolver(this);
}

DataStructures::MutableColouring* Solvers::HeuristicTreeDecompositionSolver::solve() const
{
    DataStructures::ColouringQueue rootColourings = solveAtBag(treeDecomposition->getRoot());
    return rootColourings.retrieveBestColouring();
}

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::solveAtBag(const DataStructures::NiceBag* bag) const
{
    switch(bag->getBagType())
    {
        case DataStructures::BagType::LeafBag:
            return leafBagHandler->handleLeafBag(dynamic_cast<const DataStructures::LeafBag*>(bag));
        case DataStructures::BagType::IntroduceVertexBag:
            return introduceVertexBagHandler->handleIntroduceVertexBag(dynamic_cast<const DataStructures::IntroduceVertexBag*>(bag));
        case DataStructures::BagType::ForgetVertexBag:
            return forgetVertexBagHandler->handleForgetVertexBag(dynamic_cast<const DataStructures::ForgetVertexBag*>(bag));
        case DataStructures::BagType::JoinBag:
            return joinBagHandler->handleJoinBag(dynamic_cast<const DataStructures::JoinBag*>(bag));
    }
}

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::createEmptyColouringQueue() const
{
    return DataStructures::ColouringQueue{nbSolutionsToKeep, evaluator};
}

void Solvers::BagHandler::setSolver(Solvers::HeuristicTreeDecompositionSolver* newSolver)
{
    if (!solver)
        solver = newSolver;
}
