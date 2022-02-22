//
// Created by louis on 12/12/2021.
//

#include "ConcreteJoinNodeHandlers.h"

Solvers::UseChildColoursJoinNodeHandler::UseChildColoursJoinNodeHandler(
        const Solvers::EvaluationMerger *evaluationMerger,
        double percentMustBeEqual)
    : PairwiseCombineJoinHandler{evaluationMerger, percentMustBeEqual}
{ }

void Solvers::UseChildColoursJoinNodeHandler::addMergedEntries(
        DataStructures::JoinNode *node,
        const DataStructures::TableEntry *leftEntry,
        const DataStructures::TableEntry *rightEntry) const
{
    // The colour assignments used to construct a new assignment
    std::vector<DataStructures::ColourAssignments> oldColourAssignments{leftEntry->getColourAssignments(), rightEntry->getColourAssignments()};

    // Merge the evaluation functions
    int mergedEvaluation{evaluationMerger->mergeEvaluations(leftEntry->getEvaluation(), rightEntry->getEvaluation())};

    // Insert the colour assignment in which the bag is coloured following the left entry
    DataStructures::ColourAssignments leftExtendedAssignments
    {
        leftEntry->getColourAssignments(),
        rightEntry->getColourAssignments()
    };
    node->getTable()->push(
        new DataStructures::TableEntry{
            evaluator->evaluate(verticesToColour, oldColourAssignments, leftExtendedAssignments, graph, mergedEvaluation),
            leftExtendedAssignments
        }
    );

    // Insert the colour assignment in which the bag is coloured following the right entry
    DataStructures::ColourAssignments rightExtendedAssignments
    {
        rightEntry->getColourAssignments(),
        leftEntry->getColourAssignments()
    };
    node->getTable()->push(
        new DataStructures::TableEntry{
            evaluator->evaluate(verticesToColour, oldColourAssignments, rightExtendedAssignments, graph, mergedEvaluation),
            rightExtendedAssignments
        }
    );
}
