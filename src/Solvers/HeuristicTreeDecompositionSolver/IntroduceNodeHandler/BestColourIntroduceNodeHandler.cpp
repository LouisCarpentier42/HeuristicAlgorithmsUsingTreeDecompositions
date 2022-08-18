//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "ConcreteIntroduceNodeHandlers.h"

void Solvers::BestColourIntroduceNodeHandler::handleIntroduceNode(std::shared_ptr<DataStructures::IntroduceNode>& node) const
{
    std::shared_ptr<DataStructures::NiceNode> child = node->getChild();
    solver->solveAtNode(child);

    // Nothing needs to happen for precoloured vertices
    if (graph->isPrecoloured(node->getIntroducedVertex()))
    {
        node->getTable().referenceTable(node->getChild()->getTable());
    }
    // Otherwise, the introduced vertex must be coloured
    else
    {
        // Create a table for all entries to fill up the table in the end
        DataStructures::DynamicProgrammingTable allEntries{node->getTable().getCapacity()};
        for (const std::shared_ptr<DataStructures::TableEntry>& entry : node->getChild()->getTable())
        {
            // Give the introduced vertex all possible colours and keep the best of those colours
            DataStructures::DynamicProgrammingTable table{graph->getNbColours()};
            for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
            {
                std::shared_ptr<DataStructures::ColourAssignment> entryAssignment = entry->getColourAssignments();
                std::shared_ptr<DataStructures::ColourAssignment> assignments = std::make_shared<DataStructures::ColourAssignment>(node, entryAssignment);
                assignments->assignColour(node->getIntroducedVertex(), colour);
                std::shared_ptr<DataStructures::TableEntry> newEntry = std::make_shared<DataStructures::TableEntry>(
                    evaluator->evaluate(node->getIntroducedVertex(), entryAssignment, assignments, graph, entry->getEvaluation()),
                    assignments
                );
                table.push(newEntry);
                allEntries.push(newEntry);
            }
            std::shared_ptr<DataStructures::TableEntry> bestEntry = table.getBestEntry();
            node->getTable().push(bestEntry);
            allEntries.pop(bestEntry);
        }

        // Fill the best colourings queue with extra colourings
        while (!node->getTable().hasReachedCapacity() && !allEntries.empty())
        {
            std::shared_ptr<DataStructures::TableEntry> nextBestEntry = allEntries.popBestEntry();
            node->getTable().push(nextBestEntry);
        }
    }
}
