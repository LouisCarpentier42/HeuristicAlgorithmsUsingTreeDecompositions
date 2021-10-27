//
// Created by louis on 25/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H

#include "../MaximumHappyVerticesSolver.h"

namespace MaximumHappyVertices
{
    class GreedyMHV : public MaximumHappyVerticesSolver
    {
    public:
        GreedyMHV(const DataStructures::Graph& graph, const PartialColouring& partialColouring);
        [[nodiscard]] Colouring* solve() const override;

    private:
        void colourAllVertices(Colouring* colouring, colourType colour) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H
