//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "ExactBruteForceMHV.h"
#include "../../../DataStructures/Evaluator/BasicMHVEvaluator.h"
#include "../../SolversUtility/ColouringIterator.h"

MaximumHappyVertices::ExactBruteForceMHV::ExactBruteForceMHV()
    : SolverBase{std::make_unique<DataStructures::BasicMHVEvaluator>()}
{ }

void MaximumHappyVertices::ExactBruteForceMHV::solve(std::shared_ptr<DataStructures::Graph>& graph) const
{
    std::set<DataStructures::VertexType> verticesToConsider{};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        verticesToConsider.insert(verticesToConsider.end(), vertex);
    Solvers::ColouringIterator iterator{verticesToConsider, graph};

    int bestEvaluation{-1};
    std::vector<DataStructures::ColourType> colours(graph->getNbVertices(), 0);
    do {
        DataStructures::ColourAssignment colourAssignments = iterator.getValue();
        for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
            graph->setColour(vertex, colourAssignments.getColour(vertex));

        int evaluation{evaluator->evaluate(graph)};
        if (evaluation > bestEvaluation)
        {
            bestEvaluation = evaluation;
            for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
                colours[vertex] = colourAssignments.getColour(vertex);
        }
    } while (iterator.next());

    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        graph->setColour(vertex, colours[vertex]);
}


