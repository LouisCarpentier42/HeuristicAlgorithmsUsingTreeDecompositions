//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H


#include "../../../DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "../../../DataStructures/TreeDecomposition/ForgetVertexBag.h"
#include "../../../DataStructures/TreeDecomposition/IntroduceVertexBag.h"
#include "../../../DataStructures/TreeDecomposition/JoinBag.h"
#include "../../../DataStructures/TreeDecomposition/LeafBag.h"
#include "../../../DataStructures/TreeDecomposition/NiceBag.h"
#include "../../../DataStructures/Colouring/ColouringQueue.h"

#include "../MaximumHappyVerticesSolver.h"
#include "../../SolverBase.h"

#include <queue>

namespace MaximumHappyVertices
{
    //    using ColouringQueue = std::priority_queue<DataStructures::Colouring*, std::vector<DataStructures::Colouring*>, Comparator>;

    class HeuristicTreeDecompositionSolver : public MaximumHappyVerticesSolver
    {
    private:
        const DataStructures::NiceTreeDecomposition* treeDecomposition;

    public:
        HeuristicTreeDecompositionSolver(const DataStructures::Graph* graph,
                                         const DataStructures::Colouring* partialColouring,
                                         const DataStructures::NiceTreeDecomposition* treeDecomposition);

        [[nodiscard]] DataStructures::MutableColouring* solve() const override;

    private:
        [[nodiscard]] DataStructures::ColouringQueue solveAtBag(const DataStructures::NiceBag* bag) const;
        [[nodiscard]] DataStructures::ColouringQueue handleLeafBag(const DataStructures::LeafBag* bag) const;
        [[nodiscard]] DataStructures::ColouringQueue handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag* bag) const;
        [[nodiscard]] DataStructures::ColouringQueue handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const;
        [[nodiscard]] DataStructures::ColouringQueue handleJoinBag(const DataStructures::JoinBag* bag) const;

        [[nodiscard]] DataStructures::ColouringQueue createEmptyColouringQueue() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
