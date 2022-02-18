//
// Created by louis on 18/02/2022.
//

#include "ConcreteForgetNodeHandlers.h"


void Solvers::BestColourForgetNodeHandler::handleForgetVertexBag(DataStructures::ForgetNode *node) const
{
    solver->solveAtNode(node->getChild());

    // Nothing needs to happen for precoloured vertices
    if (graph->isPrecoloured(node->getForgottenVertex()))
    {
        node->getTable()->referenceTable(node->getChild()->getTable());
    }
    // Otherwise, the introduced vertex must be coloured
    else
    {
        for (DataStructures::TableEntry* entry : *node->getChild()->getTable())
        {
            // Give the introduced vertex all possible colours and keep the best of those colours
            DataStructures::DynamicProgrammingTable table{graph->getNbColours()};
            for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
            {
                DataStructures::ColourAssignments assignments = entry->getColourAssignments();
                assignments.assignColour(node->getForgottenVertex(), colour);
                table.push(new DataStructures::TableEntry{
                    evaluator->evaluate(node->getForgottenVertex(), assignments, graph, entry->getEvaluation()),
                    assignments
                });
            }
            node->getTable()->push(table.getBestEntry());
        }
    }
}

