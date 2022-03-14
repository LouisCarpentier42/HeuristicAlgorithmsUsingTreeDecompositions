//
// Created by louis on 21/11/2021.
//

#include "ConcreteLeafNodeHandlers.h"

void Solvers::PassiveLeafNodeHandlers::handleLeafNode(std::shared_ptr<DataStructures::LeafNode>& node) const
{
    auto assignments = std::make_shared<DataStructures::ColourAssignment>(graph);
    std::set<DataStructures::VertexType> precolouredVertices{};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (graph->isPrecoloured(vertex))
        {
            assignments->assignColour(vertex, graph->getColour(vertex));
            precolouredVertices.insert(precolouredVertices.end(), vertex);
        }
    }

    std::shared_ptr<DataStructures::ColourAssignment> noColours = std::make_shared<DataStructures::ColourAssignment>(graph);
    std::shared_ptr<DataStructures::TableEntry> newEntry =
            std::make_shared<DataStructures::TableEntry>(
                evaluator->evaluate(precolouredVertices, noColours, assignments, graph, 0),
                assignments
            );
    node->getTable().push(newEntry);
}
