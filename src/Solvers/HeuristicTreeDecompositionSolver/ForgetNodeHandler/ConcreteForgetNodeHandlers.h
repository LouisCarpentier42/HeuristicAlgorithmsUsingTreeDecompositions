//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETNODEHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETNODEHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    // TODO maybe some kind of local search?
    //      -> randomly generate vertex-colour pairs and check if that assignment is better
    //      Base on existing local search algorithms for MHV
    class PassiveForgetNodeHandler : public ForgetNodeHandler
    {
    public:
        void handleForgetVertexBag(DataStructures::ForgetNode* node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEFORGETNODEHANDLERS_H
