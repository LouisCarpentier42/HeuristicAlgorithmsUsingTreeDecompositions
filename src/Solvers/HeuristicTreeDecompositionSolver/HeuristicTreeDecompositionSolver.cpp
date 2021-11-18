//
// Created by louis on 10/11/2021.
//

#include "HeuristicTreeDecompositionSolver.h"
#include "../../DataStructures/Colouring/BasicMHVEvaluator.h"

#include <algorithm>

Solvers::HeuristicTreeDecompositionSolver::HeuristicTreeDecompositionSolver(
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* partialColouring,
        const DataStructures::ColouringEvaluator* evaluator,
        size_t nbSolutionsToKeep,
        const DataStructures::NiceTreeDecomposition* treeDecomposition)
    : SolverBase(graph, partialColouring, evaluator),
      nbSolutionsToKeep{nbSolutionsToKeep},
      treeDecomposition{treeDecomposition}
{}

DataStructures::MutableColouring* Solvers::HeuristicTreeDecompositionSolver::solve() const
{
    DataStructures::ColouringQueue rootColourings = solveAtBag(treeDecomposition->getRoot());
    std::cout << "Root colourings: " << rootColourings;
    std::cout << "[MY ALGO] Evaluation:        " << evaluator->evaluate(rootColourings.retrieveBestColouring()) << "\n"; // TODO remove
    std::cout << "[MY ALGO] Nb happy vertices: " << DataStructures::BasicMHVEvaluator{graph}.evaluate(rootColourings.retrieveBestColouring()) << "\n"; // TODO remove
    return rootColourings.retrieveBestColouring();
}

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::solveAtBag(const DataStructures::NiceBag* bag) const
{
    switch(bag->getBagType())
    {
        case DataStructures::BagType::LeafBag:
            return handleLeafBag(dynamic_cast<const DataStructures::LeafBag*>(bag));
        case DataStructures::BagType::IntroduceVertexBag:
            return handleIntroduceVertexBag(dynamic_cast<const DataStructures::IntroduceVertexBag*>(bag));
        case DataStructures::BagType::ForgetVertexBag:
            return handleForgetVertexBag(dynamic_cast<const DataStructures::ForgetVertexBag*>(bag));
        case DataStructures::BagType::JoinBag:
            return handleJoinBag(dynamic_cast<const DataStructures::JoinBag*>(bag));
    }
}

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::createEmptyColouringQueue() const
{
    return DataStructures::ColouringQueue{nbSolutionsToKeep, evaluator};
}
