//
// Created by louis on 21/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINBAGHANDLERS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINBAGHANDLERS_H

#include "../HeuristicTreeDecompositionSolver.h"


// TODO ideas for join bag:
//  - when merging the colourings, when they differ to much better to skip them
//  - if left colour and right colour give equal evaluation, try to maintain both
//  - order of vertices when they are coloured during merge
//  - Use the n best colourings (attention for uncoloured vertices for only one child)

namespace Solvers
{
    class BasicJoinBagHandler : public JoinBagHandler
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
        explicit BasicJoinBagHandler(DataStructures::Graph* graph, Order order = Order::defaultOrder);
        [[nodiscard]] DataStructures::ColouringQueue handleJoinBag(const DataStructures::JoinBag* bag) const override;
    };

    class DynamicOrderJoinBagHandler : public JoinBagHandler
    {
    public:
        [[nodiscard]] DataStructures::ColouringQueue handleJoinBag(const DataStructures::JoinBag* bag) const override;
    private:
        [[nodiscard]] int nbColouredNeighbours(DataStructures::VertexType vertex, DataStructures::MutableColouring* colouring) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONCRETEJOINBAGHANDLERS_H
