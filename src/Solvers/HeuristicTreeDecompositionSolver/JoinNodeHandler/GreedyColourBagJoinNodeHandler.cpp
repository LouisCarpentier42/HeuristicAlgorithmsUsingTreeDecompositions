//
// Created by louis on 10/12/2021.
//

#include "ConcreteJoinNodeHandlers.h"

void Solvers::GreedyColourBagJoinNodeHandler::handleJoinNode(DataStructures::JoinNode* node) const
{
    solver->solveAtNode(node->getLeftChild());
    solver->solveAtNode(node->getRightChild());

    for (DataStructures::TableEntry* leftEntry : *node->getLeftChild()->getTable())
    {
        for (DataStructures::TableEntry* rightEntry : *node->getRightChild()->getTable())
        {
            // Find which vertices in the bag must be recoloured and which colours have been used
            std::vector<DataStructures::VertexType> verticesToColour(node->getBagSize());
            std::vector<bool> useColour(graph->getNbColours() + 1, false);
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                if (!graph->isPrecoloured(vertex))
                    verticesToColour.emplace_back(vertex);
                useColour[leftEntry->getColourAssignments().getColour(vertex)] = true;
                useColour[rightEntry->getColourAssignments().getColour(vertex)] = true;
            }

            // Find the best colour for the vertices in the bag
            DataStructures::TableEntry::ColourAssignments assignments
            {
                leftEntry->getColourAssignments(),
                rightEntry->getColourAssignments()
            };
            DataStructures::ColourType bestColour{0};
            int bestEvaluation{-1};
            int mergedEvaluation{evaluationMerger->mergeEvaluations(leftEntry->getEvaluation(), rightEntry->getEvaluation())};
            for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
            {
                // Only use valid colours
                if (!useColour[colour]) continue;

                // Assign the colour to the vertices
                for (DataStructures::VertexType vertex : verticesToColour)
                    assignments.assignColour(vertex, colour);

                // Compute the new evaluation and update the best colour and evaluation if needed
                int updatedEvaluation{evaluator->evaluate(verticesToColour, assignments, graph, mergedEvaluation)};
                if (updatedEvaluation > bestEvaluation)
                {
                    bestColour = colour;
                    bestEvaluation = updatedEvaluation;
                }
            }

            // Assign the best colour found to the vertices
            for (DataStructures::VertexType vertex : verticesToColour)
                assignments.assignColour(vertex, bestColour);

            node->getTable()->push(
                new DataStructures::TableEntry{
                    bestEvaluation,
                    DataStructures::TableEntry::NextEntries{leftEntry, rightEntry},
                    assignments
                }
            );
        }
    }
}
