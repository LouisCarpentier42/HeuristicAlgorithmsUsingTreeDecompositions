//
// Created by louis on 25/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H

#include "../../../DataStructures/DataStructuresAliases.h"
#include "../../../DataStructures/Graph/Graph.h"
#include "../../../DataStructures/Colouring/Colouring.h"
#include "../../../DataStructures/Colouring/MutableColouring.h"
#include "../MaximumHappyVerticesSolver.h"

namespace MaximumHappyVertices
{
    class GreedyMHV : public MaximumHappyVerticesSolver
    {
    public:
        GreedyMHV(const DataStructures::Graph* graph, const DataStructures::Colouring* colouring);
        [[nodiscard]] DataStructures::MutableColouring* solve() const override;

    private:
        void colourAllVertices(DataStructures::MutableColouring* colouringToColour, DataStructures::ColourType colour) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H
