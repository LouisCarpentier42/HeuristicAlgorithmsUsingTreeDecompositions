//
// Created by louis on 14/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGQUEUE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGQUEUE_H

#include "ColouringEvaluator.h"
#include "MutableColouring.h"

#include <vector>

namespace DataStructures
{
    class ColouringQueue
    {
    public:
        using Iterator = std::vector<DataStructures::MutableColouring*>::const_iterator;

    private:
        const size_t nbColourings;
        const ColouringEvaluator& evaluator;
        std::vector<DataStructures::MutableColouring*> queue; // TODO const?

    public:
        ColouringQueue(size_t nbColourings, const DataStructures::ColouringEvaluator& comparator);
        ~ColouringQueue();

        void push(DataStructures::MutableColouring* colouring);
        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] DataStructures::MutableColouring* retrieveBestColouring() const;

        [[nodiscard]] Iterator begin();
        [[nodiscard]] Iterator end();
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGQUEUE_H
