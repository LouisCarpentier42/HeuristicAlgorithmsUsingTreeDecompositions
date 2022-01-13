//
// Created by louis on 21/11/2021.
//

#include "ConcreteForgetNodeHandlers.h"

void Solvers::PassiveForgetNodeHandler::handleForgetVertexBag(DataStructures::ForgetNode* node) const
{
    solver->solveAtNode(node->getChild());
    node->getTable()->referenceTable(node->getChild()->getTable());
}
