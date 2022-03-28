//
// Created by louis on 17/03/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICMHVSOLVERV2_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICMHVSOLVERV2_H


#include <set>

#include "../DataStructures/TreeDecomposition/NiceNode.h"
#include "../DataStructures/TreeDecomposition/LeafNode.h"
#include "../DataStructures/TreeDecomposition/IntroduceNode.h"
#include "../DataStructures/TreeDecomposition/ForgetNode.h"
#include "../DataStructures/TreeDecomposition/JoinNode.h"
#include "../DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "HeuristicSolverRankingV2.h"

namespace SolverV2
{
    class HeuristicMHVSolverV2
    {
    public:
        enum class JoinNodeRankingOrder {
            largestRankingOut,
            smallestRankingOut
        };

    private:
        bool foundExactSolution{false};
        const int nbSolutionsToKeep;
        const int weightHappyVertices;
        const int weightPotentialHappyVertices;
        const int weightUnhappyVertices;
        const JoinNodeRankingOrder joinNodeRankingOrder;

    public:
        HeuristicMHVSolverV2(
                int nbSolutionsToKeep,
                int weightHappyVertices,
                int weightPotentialHappyVertices,
                int weightUnhappyVertices,
                JoinNodeRankingOrder joinNodeRankingOrder);

        bool hasFoundExactSolution() const;

        void solve(
                std::shared_ptr<DataStructures::Graph>& graph,
                std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition);

        [[nodiscard]] HeuristicSolverRankingV2 solveAtNode(
                const std::shared_ptr<DataStructures::NiceNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph);

    private:
        [[nodiscard]] int getEvaluation(const HappyVertexAssignmentV2& happyVertexAssignment) const;

        [[nodiscard]] HeuristicSolverRankingV2 handleLeafNode(
                const std::shared_ptr<DataStructures::LeafNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph) const;
        [[nodiscard]] HeuristicSolverRankingV2 handleIntroduceNode(
                const std::shared_ptr<DataStructures::IntroduceNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph);
        [[nodiscard]] HeuristicSolverRankingV2 handleForgetNode(
                const std::shared_ptr<DataStructures::ForgetNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph);
        [[nodiscard]] HeuristicSolverRankingV2 handleJoinNode(
                const std::shared_ptr<DataStructures::JoinNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph);

        void mergeAndAddDifferingEntries(
                SolverV2::HeuristicSolverRankingV2& ranking,
                const std::shared_ptr<DataStructures::JoinNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph,
                const HeuristicSolverRankingV2::Entry& primaryEntry,
                const HeuristicSolverRankingV2::Entry& secondaryEntry) const;
    };
}


#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICMHVSOLVERV2_H
