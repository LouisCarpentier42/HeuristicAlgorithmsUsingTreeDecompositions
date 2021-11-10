//
// Created by louis on 10/11/2021.
//

#include "HeuristicTreeDecompositionSolver.h"

MaximumHappyVertices::HeuristicTreeDecompositionSolver::HeuristicTreeDecompositionSolver(
        const DataStructures::Graph& graph,
        const DataStructures::PartialColouring& partialColouring,
        const DataStructures::TreeDecomposition& treeDecomposition)
        : MaximumHappyVerticesSolver(graph, partialColouring), treeDecomposition{treeDecomposition}
{}

DataStructures::Colouring* MaximumHappyVertices::HeuristicTreeDecompositionSolver::solve() const
{
    return nullptr; // TODO implement algorithm
}
