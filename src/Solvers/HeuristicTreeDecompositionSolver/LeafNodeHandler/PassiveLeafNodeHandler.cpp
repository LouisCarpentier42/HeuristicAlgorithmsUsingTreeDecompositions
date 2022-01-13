//
// Created by louis on 21/11/2021.
//

#include "ConcreteLeafNodeHandlers.h"

void Solvers::PassiveLeafNodeHandlers::handleLeafNode(DataStructures::LeafNode* node) const
{
    DataStructures::TableEntry::ColourAssignments assignments{graph};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        assignments.assignColour(vertex, graph->getColour(vertex));

    node->getTable()->push(
        new DataStructures::TableEntry{
            0,
            DataStructures::TableEntry::NextEntries{},
            assignments
        }
    );
}
