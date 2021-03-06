//
// Created by louis on 10/12/2021.
//

#include "ConcreteJoinNodeHandlers.h"

Solvers::GreedyColourBagJoinNodeHandler::GreedyColourBagJoinNodeHandler(
        std::shared_ptr<const EvaluationMerger>& evaluationMerger,
        double percentMustBeEqual)
    : PairwiseCombineJoinHandler{evaluationMerger, percentMustBeEqual}
{ }

void Solvers::GreedyColourBagJoinNodeHandler::addMergedEntries(
        std::shared_ptr<DataStructures::JoinNode>& node,
        const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
        const std::shared_ptr<DataStructures::TableEntry>& rightEntry) const
{
    // The colour assignments used to construct a new assignment
    std::vector<std::shared_ptr<DataStructures::ColourAssignment>> oldColourAssignments
            {leftEntry->getColourAssignments(), rightEntry->getColourAssignments()};

    // Find which vertices in the bag must be recoloured and which colours have been used
    std::vector<bool> useColour(graph->getNbColours() + 1, false);
    for (DataStructures::VertexType vertex : node->getBagContent())
    {
        useColour[leftEntry->getColourAssignments()->getColour(vertex)] = true;
        useColour[rightEntry->getColourAssignments()->getColour(vertex)] = true;
    }

    // Find the best colour for the vertices in the bag
    std::shared_ptr<DataStructures::ColourAssignment> leftEntryAssignments = leftEntry->getColourAssignments();
    std::shared_ptr<DataStructures::ColourAssignment> rightEntryAssignments = rightEntry->getColourAssignments();
    std::shared_ptr<DataStructures::ColourAssignment> assignments = std::make_shared<DataStructures::ColourAssignment>
    (
        node,
        leftEntryAssignments,
        rightEntryAssignments
    );
    DataStructures::ColourType bestColour{0};
    int bestEvaluation{-1};
    int mergedEvaluation{evaluationMerger->mergeEvaluations(leftEntry->getEvaluation(), rightEntry->getEvaluation())};
    for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
    {
        // Only use valid colours
        if (!useColour[colour]) continue;

        // Assign the colour to the vertices
        for (DataStructures::VertexType vertex : verticesToColour)
            assignments->assignColour(vertex, colour);

        // Compute the new evaluation and update the best colour and evaluation if needed
        int updatedEvaluation{evaluator->evaluate(verticesToColour, oldColourAssignments, assignments, graph, mergedEvaluation)};
        if (updatedEvaluation > bestEvaluation)
        {
            bestColour = colour;
            bestEvaluation = updatedEvaluation;
        }
    }

    // Assign the best colour found to the vertices
    for (DataStructures::VertexType vertex : verticesToColour)
        assignments->assignColour(vertex, bestColour);

    std::shared_ptr<DataStructures::TableEntry> newEntry = std::make_shared<DataStructures::TableEntry>(
            bestEvaluation,
            assignments
        );
    node->getTable().push(newEntry);
}
