//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETNODEHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETNODEHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class PassiveForgetNodeHandler : public ForgetNodeHandler
    {
    public:
        void handleForgetVertexBag(std::shared_ptr<DataStructures::ForgetNode>& node) const override;
    };

    class BestColourForgetNodeHandler : public ForgetNodeHandler
    {
    public:
        void handleForgetVertexBag(std::shared_ptr<DataStructures::ForgetNode>& node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETNODEHANDLERS_H
