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

#include <queue>

namespace MaximumHappyVertices
{
    class Comparator // TODO find location for comparator class
    {
    private:
        const DataStructures::Graph& graph;

    public:
        explicit Comparator(const DataStructures::Graph& graph) : graph{graph} {}

        bool operator()(const DataStructures::Colouring* c1, const DataStructures::Colouring* c2) const
        {
            return graph.getNbHappyVertices(c1) > graph.getNbHappyVertices(c2);
        }
    };

    using ColouringQueue = std::priority_queue<DataStructures::Colouring*, std::vector<DataStructures::Colouring*>, Comparator>;

    class HeuristicTreeDecompositionSolver : public MaximumHappyVerticesSolver
    {
    private:
        const DataStructures::NiceTreeDecomposition& treeDecomposition;

    public:
        HeuristicTreeDecompositionSolver(const DataStructures::Graph& graph,
                                         const DataStructures::PartialColouring& partialColouring,
                                         const DataStructures::NiceTreeDecomposition& treeDecomposition);

        [[nodiscard]] DataStructures::Colouring* solve() const override;

        [[nodiscard]] ColouringQueue solveAtBag(const DataStructures::NiceBag* bag) const;
        [[nodiscard]] ColouringQueue handleLeafBag(const DataStructures::LeafBag* bag) const;
        [[nodiscard]] ColouringQueue handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag* bag) const;
        [[nodiscard]] ColouringQueue handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const;
        [[nodiscard]] ColouringQueue handleJoinBag(const DataStructures::JoinBag* bag) const;

        [[nodiscard]] ColouringQueue createEmptyColouringQueue() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
