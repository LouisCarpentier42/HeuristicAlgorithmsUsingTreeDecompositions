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
        Colouring* solve() override;

    private:
        void colourAllVertices(Colouring* colouring, colourType colour);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H
