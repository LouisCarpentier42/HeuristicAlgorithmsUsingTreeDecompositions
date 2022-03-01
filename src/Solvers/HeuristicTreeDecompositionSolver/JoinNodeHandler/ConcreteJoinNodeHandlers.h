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
        std::vector<DataStructures::VertexType> verticesToColour;

    public:
        explicit PairwiseCombineJoinHandler(const EvaluationMerger* evaluationMerger, double percentMustBeEqual);
        void handleJoinNode(DataStructures::JoinNode* node) override;
        virtual void setVerticesToColour(DataStructures::JoinNode* node);
        virtual void addMergedEntries(
            DataStructures::JoinNode* node,
            DataStructures::TableEntry* leftEntry,
            DataStructures::TableEntry* rightEntry
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
    public:
        StaticOrderJoinNodeHandler(const EvaluationMerger* evaluationMerger, double percentMustBeEqual, Order order);
        void setGraph(const DataStructures::Graph* graphToSolve) override;
        void setVerticesToColour(DataStructures::JoinNode* node) override;
        void addMergedEntries(
            DataStructures::JoinNode* node,
            DataStructures::TableEntry* leftEntry,
            DataStructures::TableEntry* rightEntry
        ) const override;
    };

    class DynamicOrderJoinNodeHandler : public PairwiseCombineJoinHandler
    {
    public:
        enum class Order {
            mostColouredNeighboursFirst,
            fewestColouredNeighboursFirst,
            mostPotentialHappyNeighbours,
            mostPercentPotentialHappyNeighbours
        };

    private:
        class VertexSelector
        {
        public:
            [[nodiscard]] virtual DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                DataStructures::ColourAssignments* assignments
            ) const = 0;
        protected:
            [[nodiscard]] static int getNbColouredNeighbours(
                DataStructures::VertexType vertex,
                const DataStructures::Graph* graph,
                DataStructures::ColourAssignments* assignments
            );
            [[nodiscard]] static int getNbPotentialHappyNeighbours(
                DataStructures::VertexType vertex,
                const DataStructures::Graph* graph,
                DataStructures::ColourAssignments* assignments
            );
        };
        const VertexSelector* vertexSelector;

    public:
        DynamicOrderJoinNodeHandler(const EvaluationMerger *evaluationMerger, double percentMustBeEqual, Solvers::DynamicOrderJoinNodeHandler::Order order);
        void addMergedEntries(
            DataStructures::JoinNode* node,
            DataStructures::TableEntry* leftEntry,
            DataStructures::TableEntry* rightEntry
        ) const override;

    private:
        class MostColouredNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                DataStructures::ColourAssignments* assignments
            ) const override;
        };

        class FewestColouredNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                DataStructures::ColourAssignments* assignments
            ) const override;
        };

        class MostPotentialHappyNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                DataStructures::ColourAssignments* assignments
            ) const override;
        };

        class MostPercentPotentialHappyNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                DataStructures::ColourAssignments* assignments
            ) const override;
        };
    };

    class GreedyColourBagJoinNodeHandler : public PairwiseCombineJoinHandler
    {
    public:
        explicit GreedyColourBagJoinNodeHandler(const EvaluationMerger* evaluationMerger, double percentMustBeEqual);
//        void handleJoinNode(DataStructures::JoinNode* node) const override;
        void addMergedEntries(
            DataStructures::JoinNode* node,
            DataStructures::TableEntry* leftEntry,
            DataStructures::TableEntry* rightEntry
        ) const override;
    };

    class GrowthColourBagJoinNodeHandler : public PairwiseCombineJoinHandler
    {
    public:
        explicit GrowthColourBagJoinNodeHandler(const EvaluationMerger* evaluationMerger, double percentMustBeEqual);
        void addMergedEntries(
            DataStructures::JoinNode* node,
            DataStructures::TableEntry* leftEntry,
            DataStructures::TableEntry* rightEntry
        ) const override;
    };

    class UseChildColoursJoinNodeHandler : public PairwiseCombineJoinHandler
    {
    public:
        explicit UseChildColoursJoinNodeHandler(const EvaluationMerger* evaluationMerger, double percentMustBeEqual);
        void addMergedEntries(
            DataStructures::JoinNode* node,
            DataStructures::TableEntry* leftEntry,
            DataStructures::TableEntry* rightEntry
        ) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINNODEHANDLERS_H
