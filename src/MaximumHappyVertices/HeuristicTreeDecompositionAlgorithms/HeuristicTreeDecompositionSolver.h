//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H

#include "../MaximumHappyVerticesSolver.h"
#include "../../DataStructrures/TreeDecomposition.h"

namespace MaximumHappyVertices
{
    class HeuristicTreeDecompositionSolver : public MaximumHappyVerticesSolver
    {
    private:
        const DataStructures::TreeDecomposition& treeDecomposition;

    public:
        HeuristicTreeDecompositionSolver(const DataStructures::Graph& graph,
                                         const DataStructures::PartialColouring& partialColouring,
                                         const DataStructures::TreeDecomposition& treeDecomposition);
        [[nodiscard]] DataStructures::Colouring* solve() const override;
    };
}


#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
