//
// Created by louis on 25/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H

#include "../DataStructrures/DataStructuresAliases.h"
#include "../DataStructrures/Colouring.h"
#include "../DataStructrures/PartialColouring.h"

#include "../DataStructrures/Graph.h"

namespace MaximumHappyVertices
{
    class MaximumHappyVerticesSolver
    {
    protected:
        const DataStructures::Graph& graph;
        const DataStructures::PartialColouring& partialColouring;

    public:
        MaximumHappyVerticesSolver(const DataStructures::Graph& graph, const DataStructures::PartialColouring& partialColouring);
        [[nodiscard]] virtual DataStructures::Colouring* solve() const = 0;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H
