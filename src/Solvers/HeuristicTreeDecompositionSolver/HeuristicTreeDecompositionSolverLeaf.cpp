//
// Created by louis on 18/11/2021.
//

#include "HeuristicTreeDecompositionSolver.h"

DataStructures::ColouringQueue Solvers::HeuristicTreeDecompositionSolver::handleLeafBag(const DataStructures::LeafBag* bag) const
{
    DataStructures::ColouringQueue initialColouringQueue = createEmptyColouringQueue();
    initialColouringQueue.push(new DataStructures::MutableColouring{colouring});
    return initialColouringQueue;
}