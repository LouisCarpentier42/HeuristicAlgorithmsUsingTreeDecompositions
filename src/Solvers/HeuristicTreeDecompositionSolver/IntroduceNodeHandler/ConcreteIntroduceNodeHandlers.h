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
        void handleIntroduceNode(std::shared_ptr<DataStructures::IntroduceNode>& node) const override;
    };

    class BestColourIntroduceNodeHandler : public IntroduceNodeHandler
    {
    public:
        void handleIntroduceNode(std::shared_ptr<DataStructures::IntroduceNode>& node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEINTRODUCENODEHANDLERS_H
