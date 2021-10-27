//
// Created by louis on 27/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H

#include "../MaximumHappyVerticesSolver.h"

namespace MaximumHappyVertices
{
    class GrowthMHV : public MaximumHappyVerticesSolver
    {
    public:
        GrowthMHV(const DataStructures::Graph& graph, const PartialColouring& partialColouring);
        [[nodiscard]] Colouring* solve() const override;
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H
