//
// Created by louis on 25/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H

#include "Colouring/Colouring.h"
#include "Colouring/PartialColouring.h"

#include "../DataStructrures/Graph.h"

namespace MaximumHappyVertices
{
    class MaximumHappyVerticesSolver
    {
    protected:
        const DataStructures::Graph& graph;
        const PartialColouring& partialColouring;

    public:
        MaximumHappyVerticesSolver(const DataStructures::Graph& graph, const PartialColouring& partialColouring);
        virtual Colouring* solve() = 0;

    protected:
        unsigned int getNbHappyVertices(Colouring* colouring);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H
