//
// Created by louis on 14/11/2021.
//

#include "MaximumHappyVerticesSolver.h"

MaximumHappyVertices::MaximumHappyVerticesSolver::MaximumHappyVerticesSolver(
            const DataStructures::Graph &graph,
            const DataStructures::Colouring &colouring)
    : Solvers::SolverBase(graph, colouring, DataStructures::MHVEvaluator(graph)) {}
