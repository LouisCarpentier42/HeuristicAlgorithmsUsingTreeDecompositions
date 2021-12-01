//
// Created by louis on 21/11/2021.
//

#include "ConcreteLeafNodeHandlers.h"

DataStructures::ColouringQueue Solvers::PassiveLeafNodeHandlers::handleLeafNode(const DataStructures::LeafNode* node) const
{
    DataStructures::ColouringQueue initialColouringQueue = solver->createEmptyColouringQueue();
    initialColouringQueue.push(new DataStructures::MutableColouring{solver->colouring});
    return initialColouringQueue;
}
