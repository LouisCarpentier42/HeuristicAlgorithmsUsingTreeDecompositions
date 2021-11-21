//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H


#include "../../DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "../../DataStructures/TreeDecomposition/ForgetVertexBag.h"
#include "../../DataStructures/TreeDecomposition/IntroduceVertexBag.h"
#include "../../DataStructures/TreeDecomposition/JoinBag.h"
#include "../../DataStructures/TreeDecomposition/LeafBag.h"
#include "../../DataStructures/TreeDecomposition/NiceBag.h"
#include "../../DataStructures/Colouring/ColouringQueue.h"

#include "../SolverBase.h"

#include <queue>

namespace Solvers
{
    class LeafBagHandler;
    class IntroduceVertexBagHandler;
    class ForgetVertexBagHandler;
    class JoinBagHandler;

    class HeuristicTreeDecompositionSolver : public Solvers::SolverBase
    {
    private:
        const size_t nbSolutionsToKeep;
        const DataStructures::NiceTreeDecomposition* treeDecomposition;
        LeafBagHandler* leafBagHandler;
        IntroduceVertexBagHandler* introduceVertexBagHandler;
        ForgetVertexBagHandler* forgetVertexBagHandler;
        JoinBagHandler* joinBagHandler;

    public:
        HeuristicTreeDecompositionSolver(const DataStructures::Graph* graph,
                                         const DataStructures::Colouring* partialColouring,
                                         const DataStructures::ColouringEvaluator* evaluator,
                                         size_t nbSolutionsToKeep,
                                         const DataStructures::NiceTreeDecomposition* treeDecomposition,
                                         LeafBagHandler* leafBagHandler,
                                         IntroduceVertexBagHandler* introduceVertexBagHandler,
                                         ForgetVertexBagHandler* forgetVertexBagHandler,
                                         JoinBagHandler* joinBagHandler);

        [[nodiscard]] DataStructures::MutableColouring* solve() const override;
        [[nodiscard]] DataStructures::ColouringQueue solveAtBag(const DataStructures::NiceBag* bag) const;
        [[nodiscard]] DataStructures::ColouringQueue createEmptyColouringQueue() const;
    };

    class BagHandler
    {
    protected:
        const HeuristicTreeDecompositionSolver* solver{nullptr};

    public:
        void setSolver(HeuristicTreeDecompositionSolver* newSolver);
    };

    class LeafBagHandler : public Solvers::BagHandler
    {
    public:
        [[nodiscard]] virtual DataStructures::ColouringQueue handleLeafBag(const DataStructures::LeafBag* bag) const = 0;
    };

    class IntroduceVertexBagHandler : public Solvers::BagHandler
    {
    public:
        [[nodiscard]] virtual DataStructures::ColouringQueue handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag* bag) const = 0;
    };

    class ForgetVertexBagHandler : public Solvers::BagHandler
    {
    public:
        [[nodiscard]] virtual DataStructures::ColouringQueue handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const = 0;
    };

    class JoinBagHandler : public Solvers::BagHandler
    {
    public:
        [[nodiscard]] virtual DataStructures::ColouringQueue handleJoinBag(const DataStructures::JoinBag* bag) const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
