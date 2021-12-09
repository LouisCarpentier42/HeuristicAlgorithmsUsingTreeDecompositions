//
// Created by louis on 22/11/2021.
//

#include "ConcreteJoinNodeHandlers.h"

#include <algorithm>

DataStructures::ColouringQueue Solvers::DynamicOrderJoinNodeHandler::handleJoinNode(const DataStructures::JoinNode *node) const
{
    DataStructures::ColouringQueue leftChildSolutions = solver->solveAtNode(node->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solver->solveAtNode(node->getRightChild());

    DataStructures::ColouringQueue newSolutions = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::MutableColouring{colouring};

            for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
            {
                if (colouring->isColoured(vertex))
                    continue;
                else if (leftColouring->isColoured(vertex) && !rightColouring->isColoured(vertex))
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                else if (!leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
            }

            DataStructures::BagContent verticesToColour{node->getBagContent()};
            while (!verticesToColour.empty())
            {
                // Order: the vertex that is connected to the most coloured vertices is chosen first
                // TODO different order (eg less coloured neighbours is better
                // TODO optimize
                auto comparator = [this, newColouring](auto v1, auto v2){ return nbColouredNeighbours(v1, newColouring) < nbColouredNeighbours(v2, newColouring); };
                auto it = std::max_element(verticesToColour.begin(), verticesToColour.end(), comparator);
                DataStructures::VertexType vertex{*it};
                verticesToColour.erase(it);

                // TODO here can be done something smarter maybe?
                newColouring->setColour(vertex, leftColouring->getColour(vertex));
                int leftNbHappyVertices{evaluator->evaluate(graph, newColouring)};
                newColouring->setColour(vertex, rightColouring->getColour(vertex));
                int rightNbHappyVertices{evaluator->evaluate(graph, newColouring)};

                if (leftNbHappyVertices > rightNbHappyVertices)
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                }
            }
            newSolutions.push(newColouring);
        }
    }
    return newSolutions;
}

int Solvers::DynamicOrderJoinNodeHandler::nbColouredNeighbours(DataStructures::VertexType vertex, DataStructures::MutableColouring *colouring) const
{
    const std::vector<DataStructures::VertexType>* neighbours{graph->getNeighbours(vertex)};
    return std::count_if(neighbours->begin(), neighbours->end(),
                         [colouring](auto neighbour){ return colouring->isColoured(neighbour); });
}
