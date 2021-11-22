//
// Created by louis on 22/11/2021.
//

#include "ConcreteJoinBagHandlers.h"

#include <algorithm>

DataStructures::ColouringQueue Solvers::DynamicOrderJoinBagHandler::handleJoinBag(const DataStructures::JoinBag *bag) const
{
    DataStructures::ColouringQueue leftChildSolutions = solver->solveAtBag(bag->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solver->solveAtBag(bag->getRightChild());

    DataStructures::ColouringQueue newSolutions = solver->createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::MutableColouring{solver->colouring};

            for (DataStructures::VertexType vertex{0}; vertex < solver->graph->getNbVertices(); vertex++)
            {
                if (solver->colouring->isColoured(vertex))
                    continue;
                else if (leftColouring->isColoured(vertex) && !rightColouring->isColoured(vertex))
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                else if (!leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
            }

            DataStructures::BagContent verticesToColour{bag->getBagContent()};
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
                int leftNbHappyVertices{solver->evaluator->evaluate(newColouring)};
                newColouring->setColour(vertex, rightColouring->getColour(vertex));
                int rightNbHappyVertices{solver->evaluator->evaluate(newColouring)};

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

int Solvers::DynamicOrderJoinBagHandler::nbColouredNeighbours(DataStructures::VertexType vertex, DataStructures::MutableColouring *colouring) const
{
    const std::vector<DataStructures::VertexType>* neighbours{solver->graph->getNeighbours(vertex)};
    return std::count_if(neighbours->begin(), neighbours->end(),
                         [colouring](auto neighbour){ return colouring->isColoured(neighbour); });
}
