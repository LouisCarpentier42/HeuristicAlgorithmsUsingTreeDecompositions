//
// Created by louis on 21/11/2021.
//

#include "ConcreteForgetVertexBagHandlers.h"

DataStructures::ColouringQueue Solvers::BasicForgetVertexBagHandler::handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const
{
    return solver->solveAtBag(bag->getChild());
}
