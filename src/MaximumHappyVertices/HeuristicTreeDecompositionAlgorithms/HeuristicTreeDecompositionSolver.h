//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H

#include "../MaximumHappyVerticesSolver.h"
#include "../../DataStructrures/TreeDecomposition.h"
#include "../../DataStructrures/Bags/ForgetVertexBag.h"
#include "../../DataStructrures/Bags/IntroduceVertexBag.h"
#include "../../DataStructrures/Bags/JoinBag.h"
#include "../../DataStructrures/Bags/LeafBag.h"
#include "../../DataStructrures/Bags/NiceBag.h"

namespace MaximumHappyVertices
{
    class HeuristicTreeDecompositionSolver : public MaximumHappyVerticesSolver
    {
    private:
        const DataStructures::NiceTreeDecomposition& treeDecomposition;

    public:
        HeuristicTreeDecompositionSolver(const DataStructures::Graph& graph,
                                         const DataStructures::PartialColouring& partialColouring,
                                         const DataStructures::NiceTreeDecomposition& treeDecomposition);

        [[nodiscard]] DataStructures::Colouring* solve() const override;

        [[nodiscard]] std::vector<DataStructures::Colouring*> solveAtBag(const DataStructures::NiceBag* bag) const;
        [[nodiscard]] std::vector<DataStructures::Colouring*> handleLeafBag(const DataStructures::LeafBag* bag) const;
        [[nodiscard]] std::vector<DataStructures::Colouring*> handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag* bag) const;
        [[nodiscard]] std::vector<DataStructures::Colouring*> handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const;
        [[nodiscard]] std::vector<DataStructures::Colouring*> handleJoinBag(const DataStructures::JoinBag* bag) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
