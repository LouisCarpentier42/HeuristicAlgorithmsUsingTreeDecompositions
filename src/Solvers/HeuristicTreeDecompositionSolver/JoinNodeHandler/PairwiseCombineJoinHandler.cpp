//
// Created by louis on 21/02/2022.
//

#include "ConcreteJoinNodeHandlers.h"

#include <cmath>

Solvers::PairwiseCombineJoinHandler::PairwiseCombineJoinHandler(
        std::shared_ptr<const EvaluationMerger>& evaluationMerger, double percentMustBeEqual)
    : JoinNodeHandler{evaluationMerger}, percentMustBeEqual{percentMustBeEqual}
{ }

void Solvers::PairwiseCombineJoinHandler::setVerticesToColour(std::shared_ptr<DataStructures::JoinNode>& node)
{
    verticesToColour.clear();
    verticesToColour.resize(node->getBagSize());
    for (DataStructures::VertexType vertex : node->getBagContent())
    {
        if (!graph->isPrecoloured(vertex))
            verticesToColour.push_back(vertex);
    }
}

void Solvers::PairwiseCombineJoinHandler::handleJoinNode(std::shared_ptr<DataStructures::JoinNode>& node)
{
    std::shared_ptr<DataStructures::NiceNode> leftChild = node->getLeftChild();
    solver->solveAtNode(leftChild);
    std::shared_ptr<DataStructures::NiceNode> rightChild = node->getRightChild();
    solver->solveAtNode(rightChild);

    setVerticesToColour(node);

    bool addedAnEntry{false};
    int backupSimilarity = -1;
    const std::shared_ptr<DataStructures::TableEntry>* backupLeftEntry;
    const std::shared_ptr<DataStructures::TableEntry>* backupRightEntry;

    int nbThatMustBeEqual{static_cast<int>(std::ceil(node->getBagSize() * percentMustBeEqual))};
    for (const std::shared_ptr<DataStructures::TableEntry>& leftEntry : node->getLeftChild()->getTable())
    {
        for (const std::shared_ptr<DataStructures::TableEntry>& rightEntry : node->getRightChild()->getTable())
        {
            int nbEqualColouredVertices{0};
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                if (leftEntry->getColourAssignments()->getColour(vertex) == rightEntry->getColourAssignments()->getColour(vertex))
                {
                    nbEqualColouredVertices++;
                    if (nbEqualColouredVertices >= nbThatMustBeEqual)
                        break;
                }
            }
            if (nbEqualColouredVertices >= nbThatMustBeEqual)
            {
                addedAnEntry = true;
                addMergedEntries(node, leftEntry, rightEntry);
            }
            else if (nbEqualColouredVertices > backupSimilarity)
            {
                backupSimilarity = nbEqualColouredVertices;
                backupLeftEntry = &leftEntry;
                backupRightEntry = &rightEntry;
            }
        }
    }

    if (!addedAnEntry)
    {
        addMergedEntries(node, *backupLeftEntry, *backupRightEntry);
    }
}





