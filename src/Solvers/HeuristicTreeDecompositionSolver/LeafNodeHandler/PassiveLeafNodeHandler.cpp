//
// Created by louis on 21/11/2021.
//

#include "ConcreteLeafNodeHandlers.h"

void Solvers::PassiveLeafNodeHandlers::handleLeafNode(DataStructures::LeafNode* node) const
{
    DataStructures::ColourAssignments assignments{graph};
    std::vector<DataStructures::VertexType> precolouredVertices{};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (graph->isPrecoloured(vertex))
        {
            assignments.assignColour(vertex, graph->getColour(vertex));
            precolouredVertices.emplace_back(vertex);
        }
    }

    node->getTable()->push(
        new DataStructures::TableEntry{
            evaluator->evaluate(precolouredVertices, DataStructures::ColourAssignments{graph}, assignments, graph, 0),
            assignments
        }
    );
}
