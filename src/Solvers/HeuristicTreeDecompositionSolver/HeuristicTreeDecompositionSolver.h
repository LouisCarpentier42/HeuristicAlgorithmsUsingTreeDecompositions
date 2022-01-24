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
        size_t nbSolutionsToKeep;
        LeafNodeHandler* leafNodeHandler;
        IntroduceNodeHandler* introduceNodeHandler;
        ForgetNodeHandler* forgetNodeHandler;
        JoinNodeHandler* joinNodeHandler;

    public:
        HeuristicTreeDecompositionSolver(
            size_t nbSolutionsToKeep,
            const DataStructures::Evaluator* evaluator,
            LeafNodeHandler* leafNodeHandler,
            IntroduceNodeHandler* introduceNodeHandler,
            ForgetNodeHandler* forgetNodeHandler,
            JoinNodeHandler* joinNodeHandler
        );

        void solve(
            DataStructures::Graph* graph,
            DataStructures::NiceTreeDecomposition* treeDecomposition
        ) const;
        void solveAtNode(DataStructures::NiceNode* node) const;
    };

    class NodeHandler
    {
    public: // TODO set protected
        const DataStructures::Evaluator* evaluator{nullptr};
        const HeuristicTreeDecompositionSolver* solver{nullptr};
        DataStructures::Graph* graph{nullptr}; // TODO set constant

    public:
        void setSolverProperties(
            const DataStructures::Evaluator* newEvaluator,
            const HeuristicTreeDecompositionSolver* newSolver
        );
        void setInputInstanceProperties( // TODO set param const
            DataStructures::Graph* graphToSolve
        );

    protected:
        virtual void setEvaluator(const DataStructures::Evaluator* newEvaluator);
        virtual void setSolver(const HeuristicTreeDecompositionSolver* newSolver);
        virtual void setGraph(DataStructures::Graph* graphToSolve); // TODO set param const
    };

    class LeafNodeHandler : public Solvers::NodeHandler
    {
    public:
        virtual void handleLeafNode(DataStructures::LeafNode* node) const = 0;
    };

    class IntroduceNodeHandler : public Solvers::NodeHandler
    {
    public:
        virtual void handleIntroduceNode(DataStructures::IntroduceNode* node) const = 0;
    };

    class ForgetNodeHandler : public Solvers::NodeHandler
    {
    public:
        virtual void handleForgetVertexBag(DataStructures::ForgetNode* node) const = 0;
    };

    class JoinNodeHandler : public Solvers::NodeHandler
    {
    protected:
        const EvaluationMerger* evaluationMerger;

    public:
        explicit JoinNodeHandler(const EvaluationMerger* evaluationMerger) : evaluationMerger{evaluationMerger} {};
        virtual void handleJoinNode(DataStructures::JoinNode* node) const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICTREEDECOMPOSITIONSOLVER_H
