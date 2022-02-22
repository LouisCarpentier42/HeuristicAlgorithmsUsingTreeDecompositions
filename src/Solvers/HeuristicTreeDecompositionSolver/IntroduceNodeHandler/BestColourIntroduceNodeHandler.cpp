//
// Created by louis on 30/11/2021.
//

#include "ConcreteIntroduceNodeHandlers.h"

void Solvers::BestColourIntroduceNodeHandler::handleIntroduceNode(DataStructures::IntroduceNode *node) const
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
        // Create a table for all entries to fill up the table in the end
        DataStructures::DynamicProgrammingTable allEntries{node->getTable()->getCapacity()};
        for (DataStructures::TableEntry* entry : *node->getChild()->getTable())
        {
            // Give the introduced vertex all possible colours and keep the best of those colours
            DataStructures::DynamicProgrammingTable table{graph->getNbColours()};
            for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
            {
                DataStructures::ColourAssignments assignments = entry->getColourAssignments();
                assignments.assignColour(node->getIntroducedVertex(), colour);
                auto* newEntry = new DataStructures::TableEntry{
                    evaluator->evaluate(node->getIntroducedVertex(), entry->getColourAssignments(), assignments, graph, entry->getEvaluation()),
                    assignments
                };
                table.push(newEntry);
                allEntries.push(newEntry);
            }
            node->getTable()->push(table.getBestEntry());
        }

        // Fill the best colourings queue with extra colourings
        while (!node->getTable()->hasReachedCapacity() && !allEntries.empty())
            node->getTable()->push(allEntries.popBestEntry());
    }
}
