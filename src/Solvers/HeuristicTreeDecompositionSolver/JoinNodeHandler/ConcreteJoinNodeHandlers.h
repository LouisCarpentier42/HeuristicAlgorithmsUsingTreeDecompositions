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
        explicit StaticOrderJoinNodeHandler(Order order);
        void setGraph(const DataStructures::Graph* graphToSolve) override;
        [[nodiscard]] DataStructures::ColouringQueue handleJoinNode(const DataStructures::JoinNode* node) const override;
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
                const DataStructures::Colouring* colouring
            ) const = 0;
        protected:
            [[nodiscard]] static int getNbColouredNeighbours(
                DataStructures::VertexType vertex,
                const DataStructures::Graph* graph,
                const DataStructures::Colouring* colouring
            );
            [[nodiscard]] static int getNbPotentialHappyNeighbours(
                DataStructures::VertexType vertex,
                const DataStructures::Graph* graph,
                const DataStructures::Colouring* colouring
            );
        };
        const VertexSelector* vertexSelector;

    public:
        explicit DynamicOrderJoinNodeHandler(Order order);
        [[nodiscard]] DataStructures::ColouringQueue handleJoinNode(const DataStructures::JoinNode* node) const override;

    private:
        class MostColouredNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                const DataStructures::Colouring* colouring
            ) const override;
        };

        class FewestColouredNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                const DataStructures::Colouring* colouring
            ) const override;
        };

        class MostPotentialHappyNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                const DataStructures::Colouring* colouring
            ) const override;
        };

        class MostPercentPotentialHappyNeighboursSelector : public VertexSelector
        {
        public:
            [[nodiscard]] DataStructures::BagContent::iterator select(
                DataStructures::BagContent& bagContent,
                const DataStructures::Graph* graph,
                const DataStructures::Colouring* colouring
            ) const override;
        };
    };


    class GreedyColourBagJoinNodeHandler : public JoinNodeHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleJoinNode(const DataStructures::JoinNode* node) const override;
    };

    class GrowthColourBagJoinNodeHandler : public JoinNodeHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleJoinNode(const DataStructures::JoinNode* node) const override;
    };

    class UseChildColoursJoinNodeHandler : public JoinNodeHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleJoinNode(const DataStructures::JoinNode* node) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINNODEHANDLERS_H
