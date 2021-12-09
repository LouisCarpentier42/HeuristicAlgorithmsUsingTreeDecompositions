//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCENODEHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCENODEHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class GreedyIntroduceNodeHandler : public IntroduceNodeHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleIntroduceNode(const DataStructures::IntroduceNode* node) const override;
    };

    class BestColourIntroduceNodeHandler : public IntroduceNodeHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleIntroduceNode(const DataStructures::IntroduceNode* node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCENODEHANDLERS_H
