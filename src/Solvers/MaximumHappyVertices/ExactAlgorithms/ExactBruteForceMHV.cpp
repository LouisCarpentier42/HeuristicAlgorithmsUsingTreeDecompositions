//
// Created by louis on 13/02/2022.
//

#include "ExactBruteForceMHV.h"
#include "../../../DataStructures/Evaluator/BasicMHVEvaluator.h"
#include "../../SolversUtility/ColouringIterator.h"

MaximumHappyVertices::ExactBruteForceMHV::ExactBruteForceMHV()
    : SolverBase{new DataStructures::BasicMHVEvaluator{}}
{ }

void MaximumHappyVertices::ExactBruteForceMHV::solve(DataStructures::Graph* graph) const
{
    std::set<DataStructures::VertexType> verticesToConsider{};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        verticesToConsider.insert(verticesToConsider.end(), vertex);
    Solvers::ColouringIterator iterator{verticesToConsider, graph};

    int bestEvaluation{-1};
    DataStructures::ColourAssignments bestColourAssignments{graph};
    do {
        DataStructures::ColourAssignments colourAssignments = iterator.getValue();
        for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
            graph->setColour(vertex, colourAssignments.getColour(vertex));

        int evaluation{evaluator->evaluate(graph)};
        if (evaluation > bestEvaluation)
        {
            bestEvaluation = evaluation;
            bestColourAssignments = colourAssignments;
        }
    } while (iterator.next());

    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        graph->setColour(vertex, bestColourAssignments.getColour(vertex));
}


