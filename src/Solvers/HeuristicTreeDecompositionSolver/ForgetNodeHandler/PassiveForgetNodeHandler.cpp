//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "ConcreteForgetNodeHandlers.h"

void Solvers::PassiveForgetNodeHandler::handleForgetVertexBag(std::shared_ptr<DataStructures::ForgetNode>& node) const
{
    auto child = node->getChild();
    solver->solveAtNode(child);
    node->getTable().referenceTable(node->getChild()->getTable());
}
