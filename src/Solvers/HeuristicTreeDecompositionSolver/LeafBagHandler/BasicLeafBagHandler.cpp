//
// Created by louis on 21/11/2021.
//

#include "ConcreteLeafBagHandlers.h"

DataStructures::ColouringQueue Solvers::BasicLeafBagHandlers::handleLeafBag(const DataStructures::LeafBag *bag) const
{
    DataStructures::ColouringQueue initialColouringQueue = solver->createEmptyColouringQueue();
    initialColouringQueue.push(new DataStructures::MutableColouring{solver->colouring});
    return initialColouringQueue;
}
