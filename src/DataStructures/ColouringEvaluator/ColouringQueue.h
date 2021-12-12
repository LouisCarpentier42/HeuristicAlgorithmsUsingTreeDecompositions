//
// Created by louis on 14/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGQUEUE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGQUEUE_H

#include "ColouringEvaluator.h"
#include "../Colouring/MutableColouring.h"

#include <vector>

namespace DataStructures
{
    class ColouringQueue
    {
    public:
        using Iterator = std::vector<DataStructures::MutableColouring*>::const_iterator;

    private:
        const size_t nbColourings;
        const ColouringEvaluator* evaluator;
        const Graph* graph;
        std::vector<DataStructures::MutableColouring*> queue;

    public:
        ColouringQueue(
            size_t nbColourings,
            const DataStructures::ColouringEvaluator* evaluator,
            const DataStructures::Graph* graph
        );

        void push(DataStructures::MutableColouring* colouring);
        [[nodiscard]] DataStructures::MutableColouring* retrieveBestColouring() const;
        [[nodiscard]] DataStructures::MutableColouring* popBestColouring();

        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] bool reachedCapacity() const;

        [[nodiscard]] Iterator begin() const;
        [[nodiscard]] Iterator end() const;

        friend std::ostream& operator<<(std::ostream& out, const ColouringQueue& colouringQueue);
    };
    std::ostream& operator<<(std::ostream& out, const ColouringQueue& colouringQueue);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGQUEUE_H