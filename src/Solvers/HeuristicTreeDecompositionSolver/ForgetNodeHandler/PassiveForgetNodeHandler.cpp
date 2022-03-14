//
// Created by louis on 21/11/2021.
//

#include "ConcreteForgetNodeHandlers.h"

void Solvers::PassiveForgetNodeHandler::handleForgetVertexBag(std::shared_ptr<DataStructures::ForgetNode>& node) const
{
    auto child = node->getChild();
    solver->solveAtNode(child);
    node->getTable().referenceTable(node->getChild()->getTable());
}
