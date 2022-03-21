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

    public:
        explicit HeuristicMHVSolverV2(int nbSolutionsToKeep);

        void solve(
                std::shared_ptr<DataStructures::Graph>& graph,
                std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition) const;

        HeuristicSolverRankingV2 solveAtNode(
                const std::shared_ptr<DataStructures::NiceNode>& node,
                std::shared_ptr<DataStructures::Graph>& graph,
                std::set<DataStructures::VertexType>& S) const;

    private:
        HeuristicSolverRankingV2 handleLeafNode(
                const std::shared_ptr<DataStructures::LeafNode>& node,
                std::shared_ptr<DataStructures::Graph>& graph,
                std::set<DataStructures::VertexType>& S) const;
        HeuristicSolverRankingV2 handleIntroduceNode(
                const std::shared_ptr<DataStructures::IntroduceNode>& node,
                std::shared_ptr<DataStructures::Graph>& graph,
                std::set<DataStructures::VertexType>& S) const;
        HeuristicSolverRankingV2 handleForgetNode(
                const std::shared_ptr<DataStructures::ForgetNode>& node,
                std::shared_ptr<DataStructures::Graph>& graph,
                std::set<DataStructures::VertexType>& S) const;
        HeuristicSolverRankingV2 handleJoinNode(
                const std::shared_ptr<DataStructures::JoinNode>& node,
                std::shared_ptr<DataStructures::Graph>& graph,
                std::set<DataStructures::VertexType>& S) const;
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICMHVSOLVERV2_H
