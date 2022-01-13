//
// Created by louis on 12/12/2021.
//

#include "ConcreteJoinNodeHandlers.h"


void Solvers::UseChildColoursJoinNodeHandler::handleJoinNode(DataStructures::JoinNode *node) const
{
    solver->solveAtNode(node->getLeftChild());
    solver->solveAtNode(node->getRightChild());

    for (DataStructures::TableEntry* leftEntry : *node->getLeftChild()->getTable())
    {
        for (DataStructures::TableEntry* rightEntry : *node->getRightChild()->getTable())
        {
            // Merge the evaluation functions
            int mergedEvaluation{evaluationMerger->mergeEvaluations(leftEntry->getEvaluation(), rightEntry->getEvaluation())};

            // Insert the colour assignment in which the bag is coloured following the left entry
            DataStructures::TableEntry::ColourAssignments leftExtendedAssignments
            {
                leftEntry->getColourAssignments(),
                rightEntry->getColourAssignments()
            };
            node->getTable()->push(
                new DataStructures::TableEntry{
                    evaluator->evaluate(node->getBagContent(), leftExtendedAssignments, graph, mergedEvaluation),
                    DataStructures::TableEntry::NextEntries{leftEntry, rightEntry},
                    leftExtendedAssignments
                }
            );

            // Insert the colour assignment in which the bag is coloured following the right entry
            DataStructures::TableEntry::ColourAssignments rightExtendedAssignments
            {
                rightEntry->getColourAssignments(),
                leftEntry->getColourAssignments()
            };
            node->getTable()->push(
                new DataStructures::TableEntry{
                    evaluator->evaluate(node->getBagContent(), rightExtendedAssignments, graph, mergedEvaluation),
                    DataStructures::TableEntry::NextEntries{leftEntry, rightEntry},
                    rightExtendedAssignments
                }
            );
        }
    }
}

