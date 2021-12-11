//
// Created by louis on 14/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGEVALUATOR_H


#include "../Graph/Graph.h"
#include "../Colouring/Colouring.h"

namespace DataStructures
{
    class ColouringEvaluator
    {
    public:
        /**
         * Evaluate the given colouring.
         *
         * @param graph The graph that's used as context for the colourings.
         * @param colouring The colouring to evaluate.
         *
         * @return A value indicating how well a given colouring is. A better colouring must receive
         *         a higher evaluation value.
         */
        [[nodiscard]] virtual int evaluate(
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring
        ) const = 0;

        /**
         * Comparator function for two colourings.
         *
         * @param graph The graph that's used as context for the colourings.
         * @param c1 The first colouring to use in the comparison.
         * @param c2 The second colouring to use in the comparison.
         *
         * @return True if and only if c2 has a better evaluation than c1.
         */
        bool compare(
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* c1,
            const DataStructures::Colouring* c2
        ) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGEVALUATOR_H
