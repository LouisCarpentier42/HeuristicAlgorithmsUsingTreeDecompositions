//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCENODEHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCENODEHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class GreedyIntroduceNodeHandler : public IntroduceNodeHandler
    {
    public:
        void handleIntroduceNode(std::shared_ptr<DataStructures::IntroduceNode>& node) const override;
    };

    class BestColourIntroduceNodeHandler : public IntroduceNodeHandler
    {
    public:
        void handleIntroduceNode(std::shared_ptr<DataStructures::IntroduceNode>& node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCENODEHANDLERS_H
