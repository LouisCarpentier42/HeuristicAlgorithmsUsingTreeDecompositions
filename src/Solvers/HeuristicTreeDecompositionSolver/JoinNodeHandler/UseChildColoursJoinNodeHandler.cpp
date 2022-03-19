//
// Created by louis on 12/12/2021.
//

#include "ConcreteJoinNodeHandlers.h"

Solvers::UseChildColoursJoinNodeHandler::UseChildColoursJoinNodeHandler(
        std::shared_ptr<const EvaluationMerger>& evaluationMerger,
        double percentMustBeEqual)
    : PairwiseCombineJoinHandler{evaluationMerger, percentMustBeEqual}
{ }

void Solvers::UseChildColoursJoinNodeHandler::addMergedEntries(
        std::shared_ptr<DataStructures::JoinNode>& node,
        const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
        const std::shared_ptr<DataStructures::TableEntry>& rightEntry) const
{
    // The colour assignments used to construct a new assignment
    std::vector<std::shared_ptr<DataStructures::ColourAssignment>> oldColourAssignments{leftEntry->getColourAssignments(), rightEntry->getColourAssignments()};

    // Merge the evaluation functions
    int mergedEvaluation{evaluationMerger->mergeEvaluations(leftEntry->getEvaluation(), rightEntry->getEvaluation())};

    // Get the colour assignments of the given entries
    std::shared_ptr<DataStructures::ColourAssignment> leftEntryAssignments = leftEntry->getColourAssignments();
    std::shared_ptr<DataStructures::ColourAssignment> rightEntryAssignments = rightEntry->getColourAssignments();

    // Insert the colour assignment in which the bag is coloured following the left entry
    std::shared_ptr<DataStructures::ColourAssignment> leftExtendedAssignments = std::make_shared<DataStructures::ColourAssignment>
    (
        node,
        leftEntryAssignments,
        rightEntryAssignments
    );
    std::shared_ptr<DataStructures::TableEntry> newEntryLeft = std::make_shared<DataStructures::TableEntry>(
            evaluator->evaluate(verticesToColour, oldColourAssignments, leftExtendedAssignments, graph, mergedEvaluation),
            leftExtendedAssignments
        );
    node->getTable().push(newEntryLeft);

    // Insert the colour assignment in which the bag is coloured following the right entry
    std::shared_ptr<DataStructures::ColourAssignment> rightExtendedAssignments = std::make_shared<DataStructures::ColourAssignment>
    (
        node,
        leftEntryAssignments,
        rightEntryAssignments
    );
    std::shared_ptr<DataStructures::TableEntry> newEntryRight = std::make_shared<DataStructures::TableEntry>(
            evaluator->evaluate(verticesToColour, oldColourAssignments, rightExtendedAssignments, graph, mergedEvaluation),
            rightExtendedAssignments
        );
    node->getTable().push(newEntryRight);
}
