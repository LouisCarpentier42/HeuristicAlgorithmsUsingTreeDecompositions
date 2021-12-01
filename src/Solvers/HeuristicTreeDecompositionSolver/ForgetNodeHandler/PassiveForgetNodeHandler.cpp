//
// Created by louis on 21/11/2021.
//

#include "ConcreteForgetNodeHandlers.h"

DataStructures::ColouringQueue Solvers::PassiveForgetNodeHandler::handleForgetVertexBag(const DataStructures::ForgetNode* node) const
{
    return solver->solveAtNode(node->getChild());
}
