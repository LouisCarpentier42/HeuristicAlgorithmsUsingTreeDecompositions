//
// Created by louis on 21/11/2021.
//

#include "ConcreteIntroduceNodeHandlers.h"

void Solvers::GreedyIntroduceNodeHandler::handleIntroduceNode(std::shared_ptr<DataStructures::IntroduceNode>& node) const
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
        // Try all possible colours for the introduced vertex in all entries and keep the best entries
        for (const std::shared_ptr<DataStructures::TableEntry>& entry : node->getChild()->getTable())
        {
            for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
            {
                std::shared_ptr<DataStructures::ColourAssignment> entryAssignment = entry->getColourAssignments();
                std::shared_ptr<DataStructures::ColourAssignment> assignments = std::make_shared<DataStructures::ColourAssignment>(node, entryAssignment);
                assignments->assignColour(node->getIntroducedVertex(), colour);
                std::shared_ptr<DataStructures::TableEntry> newEntry =
                        std::make_shared<DataStructures::TableEntry>(
                            evaluator->evaluate(node->getIntroducedVertex(), entryAssignment, assignments, graph, entry->getEvaluation()),
                            assignments
                        );
                node->getTable().push(newEntry);
            }
        }
    }
}
