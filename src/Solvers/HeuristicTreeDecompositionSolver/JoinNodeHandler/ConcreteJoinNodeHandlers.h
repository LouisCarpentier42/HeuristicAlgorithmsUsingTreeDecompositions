//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINNODEHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINNODEHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"


// TODO ideas for join bag:
//  - when merging the colourings, when they differ to much better to skip them
//  - if left colour and right colour give equal evaluation, try to maintain both
//  - order of vertices when they are coloured during merge
//  - Use the n best colourings (attention for uncoloured vertices for only one child)
//  - Maybe colour vertices of bag in a growth-MHV fashion

namespace Solvers
{
    class StaticOrderJoinNodeHandler : public JoinNodeHandler
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
        StaticOrderJoinNodeHandler(const EvaluationMerger* evaluationMerger, Order order);
        void setGraph(const DataStructures::Graph* graphToSolve) override;
        void handleJoinNode(DataStructures::JoinNode* node) const override;
    };

    class DynamicOrderJoinNodeHandler : public JoinNodeHandler
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
                const DataStructures::ColourAssignments& assignments
            ) const = 0;
        protected:
            [[nodiscard]] static int getNbColouredNeighbours(
                DataStructures::VertexType vertex,
                const DataStructures::Graph* graph,
                const DataStructures::ColourAssignments& assignments
            );
            [[nodiscard]] static int getNbPotentialHappyNeighbours(
                DataStructures::VertexType vertex,
                const DataStructures::Graph* graph,
                const DataStructures::ColourAssignments& assignments
            );
        };
        const VertexSelector* vertexSelector;

    public:
        DynamicOrderJoinNodeHandler(const EvaluationMerger *evaluationMerger, Solvers::DynamicOrderJoinNodeHandler::Order order);
        void handleJoinNode(DataStructures::JoinNode* node) const override;

    private:
        class MostColouredNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                const DataStructures::ColourAssignments& assignments
            ) const override;
        };

        class FewestColouredNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                const DataStructures::ColourAssignments& assignments
            ) const override;
        };

        class MostPotentialHappyNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                const DataStructures::ColourAssignments& assignments
            ) const override;
        };

        class MostPercentPotentialHappyNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                const DataStructures::ColourAssignments& assignments
            ) const override;
        };
    };

    class GreedyColourBagJoinNodeHandler : public JoinNodeHandler
    {
    public:
        explicit GreedyColourBagJoinNodeHandler(const EvaluationMerger* evaluationMerger) : JoinNodeHandler{evaluationMerger} {};
        void handleJoinNode(DataStructures::JoinNode* node) const override;
    };

    class GrowthColourBagJoinNodeHandler : public JoinNodeHandler
    {
    public:
        explicit GrowthColourBagJoinNodeHandler(const EvaluationMerger* evaluationMerger) : JoinNodeHandler{evaluationMerger} {};
        void handleJoinNode(DataStructures::JoinNode* node) const override;
    };

    class UseChildColoursJoinNodeHandler : public JoinNodeHandler
    {
    public:
        explicit UseChildColoursJoinNodeHandler(const EvaluationMerger* evaluationMerger) : JoinNodeHandler{evaluationMerger} {};
        void handleJoinNode(DataStructures::JoinNode* node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINNODEHANDLERS_H
