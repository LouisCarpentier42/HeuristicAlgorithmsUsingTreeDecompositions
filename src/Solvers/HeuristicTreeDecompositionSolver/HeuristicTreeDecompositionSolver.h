//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H


#include "../../DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "../../DataStructures/TreeDecomposition/ForgetNode.h"
#include "../../DataStructures/TreeDecomposition/IntroduceNode.h"
#include "../../DataStructures/TreeDecomposition/JoinNode.h"
#include "../../DataStructures/TreeDecomposition/LeafNode.h"
#include "../../DataStructures/TreeDecomposition/NiceNode.h"

#include "../../DataStructures/Evaluator/Evaluator.h"

#include "JoinNodeHandler/EvaluationMerger.h"

namespace Solvers
{
    class LeafNodeHandler;
    class IntroduceNodeHandler;
    class ForgetNodeHandler;
    class JoinNodeHandler;

    class HeuristicTreeDecompositionSolver
    {
    private:
        size_t nbSolutionsToKeep{1};
        std::shared_ptr<LeafNodeHandler> leafNodeHandler;
        std::shared_ptr<IntroduceNodeHandler> introduceNodeHandler;
        std::shared_ptr<ForgetNodeHandler> forgetNodeHandler;
        std::shared_ptr<JoinNodeHandler> joinNodeHandler;

    public:
        HeuristicTreeDecompositionSolver(
            size_t nbSolutionsToKeep,
            std::shared_ptr<DataStructures::Evaluator> evaluator,
            std::shared_ptr<LeafNodeHandler>& leafNodeHandler,
            std::shared_ptr<IntroduceNodeHandler>& introduceNodeHandler,
            std::shared_ptr<ForgetNodeHandler>& forgetNodeHandler,
            std::shared_ptr<JoinNodeHandler>& joinNodeHandler
        );

        void solve(
            std::shared_ptr<DataStructures::Graph>& graph,
            std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition
        ) const;
        void solveAtNode(std::shared_ptr<DataStructures::NiceNode>& node) const;
    };

    class NodeHandler
    {
    protected:
        std::shared_ptr<DataStructures::Evaluator> evaluator{};
        HeuristicTreeDecompositionSolver* solver{};
        std::shared_ptr<DataStructures::Graph> graph{};

    public:
        void setSolverProperties(
            std::shared_ptr<DataStructures::Evaluator>& newEvaluator,
            HeuristicTreeDecompositionSolver* newSolver
        );
        void setInputInstanceProperties(
            std::shared_ptr<DataStructures::Graph>& graphToSolve
        );

    protected:
        virtual void setEvaluator(std::shared_ptr<DataStructures::Evaluator>& newEvaluator);
        virtual void setSolver(HeuristicTreeDecompositionSolver* newSolver);
        virtual void setGraph(std::shared_ptr<DataStructures::Graph>& graphToSolve);
    };

    class LeafNodeHandler : public Solvers::NodeHandler
    {
    public:
        virtual void handleLeafNode(std::shared_ptr<DataStructures::LeafNode>& node) const = 0;
    };

    class IntroduceNodeHandler : public Solvers::NodeHandler
    {
    public:
        virtual void handleIntroduceNode(std::shared_ptr<DataStructures::IntroduceNode>& node) const = 0;
    };

    class ForgetNodeHandler : public Solvers::NodeHandler
    {
    public:
        virtual void handleForgetVertexBag(std::shared_ptr<DataStructures::ForgetNode>& node) const = 0;
    };

    class JoinNodeHandler : public Solvers::NodeHandler
    {
    protected:
        std::shared_ptr<const EvaluationMerger> evaluationMerger;

    public:
        explicit JoinNodeHandler(std::shared_ptr<const EvaluationMerger>& evaluationMerger) : evaluationMerger{evaluationMerger} {};
        virtual void handleJoinNode(std::shared_ptr<DataStructures::JoinNode>& node) = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
