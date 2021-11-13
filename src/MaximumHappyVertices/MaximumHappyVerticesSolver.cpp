//
// Created by louis on 25/10/2021.
//

#include "MaximumHappyVerticesSolver.h"

MaximumHappyVertices::MaximumHappyVerticesSolver::MaximumHappyVerticesSolver(
        const DataStructures::Graph& graph,
        const DataStructures::PartialColouring& partialColouring)
        : graph{graph}, partialColouring{partialColouring}
{}
