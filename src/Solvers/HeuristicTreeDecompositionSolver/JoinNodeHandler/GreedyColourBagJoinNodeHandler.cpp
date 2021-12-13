//
// Created by louis on 10/12/2021.
//

#include "ConcreteJoinNodeHandlers.h"

#include <set>

DataStructures::ColouringQueue Solvers::GreedyColourBagJoinNodeHandler::handleJoinNode(const DataStructures::JoinNode* node) const
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

            DataStructures::BagContent verticesToColour(node->getBagSize());
            std::vector<bool> useColour(colouring->getNbColours());
//            std::set<DataStructures::ColourType> coloursToUse{};
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                if (!colouring->isColoured(vertex))
                {
                    verticesToColour.push_back(vertex);
                }
                useColour[leftColouring->getColour(vertex)] = true;
                useColour[rightColouring->getColour(vertex)] = true;
            }

            DataStructures::ColourType bestColour{0};
            int bestEval{-1};
//            for (DataStructures::ColourType colour : coloursToUse)
            for (DataStructures::ColourType colour{1}; colour <= colouring->getNbColours(); colour++)
            {
                if (!useColour[colour]) continue;
                for (DataStructures::VertexType vertex : verticesToColour)
                    newColouring->setColour(vertex, colour);
                int eval{evaluator->evaluate(graph, newColouring)};
                if (eval > bestEval)
                {
                    bestColour = colour;
                    bestEval = eval;
                }
            }
            for (DataStructures::VertexType vertex : verticesToColour)
                newColouring->setColour(vertex, bestColour);

            newSolutions.push(newColouring);
        }
    }
    return newSolutions;
}
