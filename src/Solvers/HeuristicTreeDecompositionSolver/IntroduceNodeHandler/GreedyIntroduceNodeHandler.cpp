//
// Created by louis on 21/11/2021.
//

#include "ConcreteIntroduceNodeHandlers.h"

void Solvers::GreedyIntroduceNodeHandler::handleIntroduceNode(DataStructures::IntroduceNode* node) const
{
    solver->solveAtNode(node->getChild());

    // Nothing needs to happen for precoloured vertices
    if (graph->isPrecoloured(node->getIntroducedVertex()))
    {
        node->getTable()->referenceTable(node->getChild()->getTable());
    }
    // Otherwise, the introduced vertex must be coloured
    else
    {
        // Try all possible colours for the introduced vertex in all entries and keep the best entries
        for (DataStructures::TableEntry* entry : *node->getChild()->getTable())
        {
            for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
            {
                DataStructures::ColourAssignments assignments = entry->getColourAssignments();
                assignments.assignColour(node->getIntroducedVertex(), colour);
                node->getTable()->push(
                    new DataStructures::TableEntry{
                        evaluator->evaluate(node->getIntroducedVertex(), entry->getColourAssignments(), assignments, graph, entry->getEvaluation()),
                        assignments
                    }
                );
            }
        }
    }
}
