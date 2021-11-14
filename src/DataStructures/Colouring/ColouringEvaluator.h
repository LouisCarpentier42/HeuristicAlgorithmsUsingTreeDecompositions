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
    protected:
        /** The graph that is used for the comparison of colourings. **/
        const DataStructures::Graph* graph;

    public:
        explicit ColouringEvaluator(const DataStructures::Graph* graph);

        /**
         * Evaluate the given colouring.
         *
         * @param colouring The colouring to evaluate.
         *
         * @return A value indicating how well a given colouring is. A better colouring must receive
         *         a higher evaluation value.
         */
        [[nodiscard]] virtual int evaluate(const DataStructures::Colouring* colouring) const = 0;

        /**
         * Comparator function for two colourings.
         *
         * @param c1 The first colouring to use in the comparison.
         * @param c2 The second colouring to use in the comparison.
         *
         * @return True if and only if c1 has a better evaluation than c2.
         */
        bool operator()(const DataStructures::Colouring* c1, const DataStructures::Colouring* c2) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGEVALUATOR_H
