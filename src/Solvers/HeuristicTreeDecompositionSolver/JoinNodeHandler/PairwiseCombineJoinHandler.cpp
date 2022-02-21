//
// Created by louis on 21/02/2022.
//

#include "ConcreteJoinNodeHandlers.h"

#include <cmath>

Solvers::PairwiseCombineJoinHandler::PairwiseCombineJoinHandler(
        const Solvers::EvaluationMerger* evaluationMerger, double percentMustBeEqual)
    : JoinNodeHandler{evaluationMerger}, percentMustBeEqual{percentMustBeEqual}
{ }

void Solvers::PairwiseCombineJoinHandler::setVerticesToColour(DataStructures::JoinNode *node)
{
    verticesToColour.clear();
    verticesToColour.resize(node->getBagSize());
    for (DataStructures::VertexType vertex : node->getBagContent())
    {
        if (!graph->isPrecoloured(vertex))
            verticesToColour.push_back(vertex);
    }
}

void Solvers::PairwiseCombineJoinHandler::handleJoinNode(DataStructures::JoinNode* node)
{
    solver->solveAtNode(node->getLeftChild());
    solver->solveAtNode(node->getRightChild());

    setVerticesToColour(node);

    int nbThatMustBeEqual{static_cast<int>(std::ceil(node->getBagSize() * percentMustBeEqual))};

    for (DataStructures::TableEntry* leftEntry : *node->getLeftChild()->getTable())
    {
        for (DataStructures::TableEntry* rightEntry : *node->getRightChild()->getTable())
        {
            int nbEqualColouredVertices{0};
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                if (leftEntry->getColourAssignments().getColour(vertex) == rightEntry->getColourAssignments().getColour(vertex))
                {
                    nbEqualColouredVertices++;
                    if (nbEqualColouredVertices >= nbThatMustBeEqual)
                        break;
                }
            }
            if (nbEqualColouredVertices >= nbThatMustBeEqual)
            {
                addMergedEntries(node, leftEntry, rightEntry);
            }
        }
    }
}





