//
// Created by louis on 18/11/2021.
//

#include "HeuristicTreeDecompositionSolver.h"

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const
{
    return solveAtBag(bag->getChild());
}