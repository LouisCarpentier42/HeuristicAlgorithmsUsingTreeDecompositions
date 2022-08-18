//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "ConcreteForgetNodeHandlers.h"


void Solvers::BestColourForgetNodeHandler::handleForgetVertexBag(std::shared_ptr<DataStructures::ForgetNode>& node) const
{
    std::shared_ptr<DataStructures::NiceNode> child = node->getChild();
    solver->solveAtNode(child);

    // Nothing needs to happen for precoloured vertices
    if (graph->isPrecoloured(node->getForgottenVertex()))
    {
        node->getTable().referenceTable(node->getChild()->getTable());
    }
    // Otherwise, the introduced vertex must be coloured
    else
    {
        for (const std::shared_ptr<DataStructures::TableEntry>& entry : node->getChild()->getTable())
        {
            // Give the introduced vertex all possible colours and keep the best of those colours
            DataStructures::DynamicProgrammingTable table{graph->getNbColours()};
            for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
            {
                std::shared_ptr<DataStructures::ColourAssignment> entryAssignment = entry->getColourAssignments();
                std::shared_ptr<DataStructures::ColourAssignment> assignments = std::make_shared<DataStructures::ColourAssignment>(node, entryAssignment);
                assignments->assignColour(node->getForgottenVertex(), colour);
                std::shared_ptr<DataStructures::TableEntry> newEntry =
                        std::make_unique<DataStructures::TableEntry>(
                            evaluator->evaluate(node->getForgottenVertex(), entryAssignment, assignments, graph, entry->getEvaluation()),
                            assignments
                        );
                table.push(newEntry);
            }
            std::shared_ptr<DataStructures::TableEntry> bestEntry = table.getBestEntry();
            node->getTable().push(bestEntry);
        }
    }
}

