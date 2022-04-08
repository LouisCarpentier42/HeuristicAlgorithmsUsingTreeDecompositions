//
// Created by louis on 17/03/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICMHVSOLVERV2_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICMHVSOLVERV2_H


#include <set>
#include <queue>

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
            smallestRankingOut,
            randomRankingOut
        };
        enum class VertexWeightJoinBag {
            unitary,
            nbColouredNeighboursOutsideBag,
            hasColouredNeighbourOutsideBag,
            nbNeighboursOutsideBag,
            hasNeighboursOutsideBag,
            nbNeighboursInBorder,
            hasNeighbourInBorder
        };
        enum class JoinNodeCombineHeuristic {
            copyBag,
            merge
        };

    private:
        bool foundExactSolution{false};
    public:
        const int nbSolutionsToKeep;
        const int weightHappyVertices;
        const int weightPotentialHappyVertices;
        const int weightUnhappyVertices;
        const int weightPotentialUnhappyVertices;
        const JoinNodeRankingOrder joinNodeRankingOrder;
        const VertexWeightJoinBag vertexWeightJoinBag;
        const JoinNodeCombineHeuristic joinNodeCombineHeuristic;

    public:
        HeuristicMHVSolverV2(
                int nbSolutionsToKeep,
                int weightHappyVertices,
                int weightPotentialHappyVertices,
                int weightUnhappyVertices,
                int weightPotentialUnhappyVertices,
                JoinNodeRankingOrder joinNodeRankingOrder,
                VertexWeightJoinBag vertexWeightJoinBag,
                JoinNodeCombineHeuristic joinNodeCombineHeuristic);

        [[nodiscard]] bool hasFoundExactSolution() const;

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

        void copyBag(
                SolverV2::HeuristicSolverRankingV2& ranking,
                const std::shared_ptr<DataStructures::JoinNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph,
                HeuristicSolverRankingV2::Entry& primaryEntry,
                HeuristicSolverRankingV2::Entry& secondaryEntry,
                const std::set<DataStructures::VertexType>& verticesBorderSecondary,
                const std::deque<DataStructures::VertexType>& verticesInBagConnectingSecondary) const;
        void merge(
                SolverV2::HeuristicSolverRankingV2& ranking,
                const std::shared_ptr<DataStructures::JoinNode>& node,
                const std::shared_ptr<DataStructures::Graph>& graph,
                HeuristicSolverRankingV2::Entry& primaryEntry,
                HeuristicSolverRankingV2::Entry& secondaryEntry) const;
        static void colourNeighboursWithSameColour(
                const std::shared_ptr<DataStructures::Graph>& graph,
                SolverV2::HeuristicSolverRankingV2::Entry& primaryEntry,
                SolverV2::HeuristicSolverRankingV2::Entry& secondaryEntry,
                DataStructures::VertexType vertex,
                SolverV2::ColourAssignmentV2& mergedColouring,
                SolverV2::HappyVertexAssignmentV2& mergedHappiness,
                std::map<DataStructures::VertexType, DataStructures::ColourType>& potentialHappyNeighbours,
                std::queue<DataStructures::VertexType>& colouredVerticesWithoutHappiness);
        static void processQueue(
                const std::shared_ptr<DataStructures::Graph>& graph,
                SolverV2::HeuristicSolverRankingV2::Entry& primaryEntry,
                SolverV2::HeuristicSolverRankingV2::Entry& secondaryEntry,
                SolverV2::ColourAssignmentV2& mergedColouring,
                SolverV2::HappyVertexAssignmentV2& mergedHappiness,
                std::map<DataStructures::VertexType, DataStructures::ColourType>& potentialHappyNeighbours,
                std::queue<DataStructures::VertexType>& colouredVerticesWithoutHappiness);
    };
}


#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICMHVSOLVERV2_H
