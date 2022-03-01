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
    std::vector<DataStructures::ColourType> colours(graph->getNbVertices(), 0);
    do {
        DataStructures::ColourAssignments colourAssignments = iterator.getValue();
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


