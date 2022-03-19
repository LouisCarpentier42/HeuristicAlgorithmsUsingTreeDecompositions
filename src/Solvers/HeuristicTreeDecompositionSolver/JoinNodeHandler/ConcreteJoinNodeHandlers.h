//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINNODEHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINNODEHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"

namespace Solvers
{
    class PairwiseCombineJoinHandler : public JoinNodeHandler
    {
    private:
        const double percentMustBeEqual;

    protected:
        std::set<DataStructures::VertexType> verticesToColour;

    public:
        explicit PairwiseCombineJoinHandler(std::shared_ptr<const EvaluationMerger>& evaluationMerger, double percentMustBeEqual);
        void handleJoinNode(std::shared_ptr<DataStructures::JoinNode>& node) override;
        virtual void setVerticesToColour(std::shared_ptr<DataStructures::JoinNode>& node);
        virtual void addMergedEntries(
            std::shared_ptr<DataStructures::JoinNode>& node,
            const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
            const std::shared_ptr<DataStructures::TableEntry>& rightEntry
        ) const = 0;
    };

    class StaticOrderJoinNodeHandler : public PairwiseCombineJoinHandler
    {
    public:
        enum class Order {
            defaultOrder,
            greatestDegreeFirst,
            smallestDegreeFirst,
            random
        };
    private:
        const Order order;
        std::vector<DataStructures::VertexType> vertexOrder;
        std::vector<DataStructures::VertexType> vertexOrderToColour;
    public:
        StaticOrderJoinNodeHandler(std::shared_ptr<const EvaluationMerger>& evaluationMerger, double percentMustBeEqual, Order order);
        void setGraph(std::shared_ptr<DataStructures::Graph>& graphToSolve) override;
        void setVerticesToColour(std::shared_ptr<DataStructures::JoinNode>& node) override;
        void addMergedEntries(
            std::shared_ptr<DataStructures::JoinNode>& node,
            const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
            const std::shared_ptr<DataStructures::TableEntry>& rightEntry
        ) const override;
    };

    class DynamicOrderJoinNodeHandler : public PairwiseCombineJoinHandler
    {
    public:
        enum class Order {
            mostColouredNeighboursFirst,
            fewestColouredNeighboursFirst,
            mostSameColouredNeighboursFirst,
            mostPercentSameColouredNeighboursFirst
        };

    private:
        class VertexSelector
        {
        protected:
            std::map<DataStructures::VertexType, double> scores{};

        public:
            virtual void initializeScores(
                const std::set<DataStructures::VertexType>& verticesToColour,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) = 0;
            virtual void updateScores(
                DataStructures::VertexType colouredVertex,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) = 0;
            [[nodiscard]] DataStructures::VertexType popBest();
            [[nodiscard]] bool hasScoresLeft();

        protected:
            [[nodiscard]] static int getNbColouredNeighbours(
                DataStructures::VertexType vertex,
                std::shared_ptr<DataStructures::ColourAssignment>& assignments,
                const std::shared_ptr<DataStructures::Graph>& graph
            );
        };
        std::unique_ptr<VertexSelector> vertexSelector;

    public:
        DynamicOrderJoinNodeHandler(std::shared_ptr<const EvaluationMerger>& evaluationMerger, double percentMustBeEqual, Solvers::DynamicOrderJoinNodeHandler::Order order);
        void addMergedEntries(
            std::shared_ptr<DataStructures::JoinNode>& node,
            const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
            const std::shared_ptr<DataStructures::TableEntry>& rightEntry
        ) const override;

    private:
        class MostColouredNeighboursSelector : public VertexSelector
        {
        public:
            void initializeScores(
                const std::set<DataStructures::VertexType>& verticesToColour,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) override;
            void updateScores(
                DataStructures::VertexType colouredVertex,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) override;
        };

        class FewestColouredNeighboursSelector : public VertexSelector
        {
        public:
            void initializeScores(
                const std::set<DataStructures::VertexType>& verticesToColour,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) override;
            void updateScores(
                DataStructures::VertexType colouredVertex,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) override;
        };

        class MostSameColouredNeighboursFirst : public VertexSelector
        {
        private:
            std::map<DataStructures::VertexType, DataStructures::ColourType> cachedColourNeighbours{};
        public:
            void initializeScores(
                const std::set<DataStructures::VertexType>& verticesToColour,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) override;
            void updateScores(
                DataStructures::VertexType colouredVertex,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) override;
        };

        class MostPercentSameColouredNeighboursFirst : public VertexSelector
        {
        private:
            std::map<DataStructures::VertexType, DataStructures::ColourType> cachedColourNeighbours{};
        public:
            void initializeScores(
                const std::set<DataStructures::VertexType>& verticesToColour,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) override;
            void updateScores(
                DataStructures::VertexType colouredVertex,
                std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
                const std::shared_ptr<DataStructures::Graph>& graph
            ) override;
        };
    };

    class GreedyColourBagJoinNodeHandler : public PairwiseCombineJoinHandler
    {
    public:
        explicit GreedyColourBagJoinNodeHandler(std::shared_ptr<const EvaluationMerger>& evaluationMerger, double percentMustBeEqual);
        void addMergedEntries(
            std::shared_ptr<DataStructures::JoinNode>& node,
            const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
            const std::shared_ptr<DataStructures::TableEntry>& rightEntry
        ) const override;
    };

    class GrowthColourBagJoinNodeHandler : public PairwiseCombineJoinHandler
    {
    public:
        explicit GrowthColourBagJoinNodeHandler(std::shared_ptr<const EvaluationMerger>& evaluationMerger, double percentMustBeEqual);
        void addMergedEntries(
            std::shared_ptr<DataStructures::JoinNode>& node,
            const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
            const std::shared_ptr<DataStructures::TableEntry>& rightEntry
        ) const override;
    };

    class UseChildColoursJoinNodeHandler : public PairwiseCombineJoinHandler
    {
    public:
        explicit UseChildColoursJoinNodeHandler(std::shared_ptr<const EvaluationMerger>& evaluationMerger, double percentMustBeEqual);
        void addMergedEntries(
            std::shared_ptr<DataStructures::JoinNode>& node,
            const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
            const std::shared_ptr<DataStructures::TableEntry>& rightEntry
        ) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINNODEHANDLERS_H
