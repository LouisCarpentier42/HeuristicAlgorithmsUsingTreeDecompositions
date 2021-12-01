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
        std::vector<DataStructures::VertexType> vertexOrder;
    public:
        explicit StaticOrderJoinNodeHandler(DataStructures::Graph* graph, Order order = Order::defaultOrder);
        [[nodiscard]] DataStructures::ColouringQueue handleJoinNode(const DataStructures::JoinNode* node) const override;
    };

    class DynamicOrderJoinNodeHandler : public JoinNodeHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleJoinNode(const DataStructures::JoinNode* node) const override;
    private:
        [[nodiscard]] int nbColouredNeighbours(DataStructures::VertexType vertex, DataStructures::MutableColouring* colouring) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINNODEHANDLERS_H
