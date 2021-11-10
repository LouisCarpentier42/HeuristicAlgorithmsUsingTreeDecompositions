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
        GreedyMHV(const DataStructures::Graph& graph, const DataStructures::PartialColouring& partialColouring);
        [[nodiscard]] DataStructures::Colouring* solve() const override;

    private:
        void colourAllVertices(DataStructures::Colouring* colouring, DataStructures::ColourType colour) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H
