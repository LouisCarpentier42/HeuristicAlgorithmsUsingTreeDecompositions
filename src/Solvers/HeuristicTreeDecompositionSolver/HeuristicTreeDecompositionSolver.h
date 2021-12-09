//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H


#include "../../DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "../../DataStructures/TreeDecomposition/ForgetNode.h"
#include "../../DataStructures/TreeDecomposition/IntroduceNode.h"
#include "../../DataStructures/TreeDecomposition/JoinNode.h"
#include "../../DataStructures/TreeDecomposition/LeafNode.h"
#include "../../DataStructures/TreeDecomposition/NiceNode.h"
#include "../../DataStructures/Colouring/ColouringQueue.h"

#include "../SolverBase.h"

#include <queue>

namespace Solvers
{
    class LeafNodeHandler;
    class IntroduceNodeHandler;
    class ForgetNodeHandler;
    class JoinNodeHandler;

    class HeuristicTreeDecompositionSolver
    {
    private:

//        /** Variable referring to the number of solutions that should be kept at each node. **/
//        const size_t nbSolutionsToKeep;
//
//        const DataStructures::ColouringEvaluator* evaluator;

//        /** The nice tree decomposition to use during when solving the problem. **/
//        const DataStructures::NiceTreeDecomposition* treeDecomposition;

        /** Objects that should handle the different types of nodes of the tree decomposition. **/
        LeafNodeHandler* leafNodeHandler;
        IntroduceNodeHandler* introduceNodeHandler;
        ForgetNodeHandler* forgetNodeHandler;
        JoinNodeHandler* joinNodeHandler;

    public:
        HeuristicTreeDecompositionSolver(
            size_t nbSolutionsToKeep,
            const DataStructures::ColouringEvaluator* evaluator,
            LeafNodeHandler* leafNodeHandler,
            IntroduceNodeHandler* introduceNodeHandler,
            ForgetNodeHandler* forgetNodeHandler,
            JoinNodeHandler* joinNodeHandler
        );
//        HeuristicTreeDecompositionSolver(const DataStructures::Graph* graph,
//                                         const DataStructures::Colouring* partialColouring,
//                                         const DataStructures::ColouringEvaluator* evaluator,
//                                         size_t nbSolutionsToKeep,
//                                         const DataStructures::NiceTreeDecomposition* treeDecomposition,
//                                         LeafNodeHandler* leafNodeHandler,
//                                         IntroduceNodeHandler* introduceNodeHandler,
//                                         ForgetNodeHandler* forgetNodeHandler,
//                                         JoinNodeHandler* joinNodeHandler);

        [[nodiscard]] DataStructures::MutableColouring* solve(
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring,
            const DataStructures::NiceTreeDecomposition* treeDecomposition
        ) const;
//        [[nodiscard]] DataStructures::MutableColouring* solve() const override;
        [[nodiscard]] DataStructures::ColouringQueue solveAtNode(const DataStructures::NiceNode* node) const;
//        [[nodiscard]] DataStructures::ColouringQueue createEmptyColouringQueue() const;
    };

    class NodeHandler
    {
    protected:
        size_t nbSolutionsToKeep{};
        const DataStructures::ColouringEvaluator* evaluator{nullptr};
        const HeuristicTreeDecompositionSolver* solver{nullptr};
        const DataStructures::Graph* graph{nullptr};
        const DataStructures::Colouring* colouring{nullptr};

    public:
        void setSolverProperties(
            size_t newNbSolutionsToKeep,
            const DataStructures::ColouringEvaluator* newEvaluator,
            const HeuristicTreeDecompositionSolver* newSolver
        );
        void setInputInstanceProperties(
            const DataStructures::Graph* graphToSolve,
            const DataStructures::Colouring* colouringToSolve
        );

    protected:
        [[nodiscard]] DataStructures::ColouringQueue createEmptyColouringQueue() const;
    };

    class LeafNodeHandler : public Solvers::NodeHandler
    {
    public:
        [[nodiscard]] virtual DataStructures::ColouringQueue handleLeafNode(const DataStructures::LeafNode* node) const = 0;
    };

    class IntroduceNodeHandler : public Solvers::NodeHandler
    {
    public:
        [[nodiscard]] virtual DataStructures::ColouringQueue handleIntroduceNode(const DataStructures::IntroduceNode* node) const = 0;
    };

    class ForgetNodeHandler : public Solvers::NodeHandler
    {
    public:
        [[nodiscard]] virtual DataStructures::ColouringQueue handleForgetVertexBag(const DataStructures::ForgetNode* node) const = 0;
    };

    class JoinNodeHandler : public Solvers::NodeHandler
    {
    public:
        [[nodiscard]] virtual DataStructures::ColouringQueue handleJoinNode(const DataStructures::JoinNode* node) const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
