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
    private:
        const int nbSolutionsToKeep;
        const int weightHappyVertices{2};
        const int weightPotentialHappyVertices{1};
        const int weightUnhappyVertices{0};

    public:
        explicit HeuristicMHVSolverV2(int nbSolutionsToKeep);

        void solve(
                std::shared_ptr<DataStructures::Graph>& graph,
                std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition) const;

        [[nodiscard]] HeuristicSolverRankingV2 solveAtNode(
                const std::shared_ptr<DataStructures::NiceNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph,
                const std::set<DataStructures::VertexType>& S) const;

    private:
        [[nodiscard]] int getEvaluation(const HappyVertexAssignmentV2& happyVertexAssignment) const;

        [[nodiscard]] HeuristicSolverRankingV2 handleLeafNode(
                const std::shared_ptr<DataStructures::LeafNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph,
                const std::set<DataStructures::VertexType>& S) const;
        [[nodiscard]] HeuristicSolverRankingV2 handleIntroduceNode(
                const std::shared_ptr<DataStructures::IntroduceNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph,
                const std::set<DataStructures::VertexType>& S) const;
        [[nodiscard]] HeuristicSolverRankingV2 handleForgetNode(
                const std::shared_ptr<DataStructures::ForgetNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph,
                const std::set<DataStructures::VertexType>& S) const;
        [[nodiscard]] HeuristicSolverRankingV2 handleJoinNode(
                const std::shared_ptr<DataStructures::JoinNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph,
                const std::set<DataStructures::VertexType>& S) const;

        void mergeAndAddDifferingEntries(
                SolverV2::HeuristicSolverRankingV2& ranking,
                const std::shared_ptr<DataStructures::JoinNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph,
                const ColourAssignmentV2& primaryColouring,
                const SolverV2::HappyVertexAssignmentV2& primaryHappiness,
                int evaluationPrimary,
                const ColourAssignmentV2& secondaryColouring,
                const SolverV2::HappyVertexAssignmentV2& secondaryHappiness,
                int evaluationSecondary) const;
    };
}


#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICMHVSOLVERV2_H
