//
// Created by louis on 25/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H

#include "../../../DataStructures/DataStructuresAliases.h"
#include "../../../DataStructures/Graph/Graph.h"
#include "../MaximumHappyVerticesSolver.h"

namespace MaximumHappyVertices
{
    class GreedyMHV : public MaximumHappyVerticesSolver
    {
    public:
        GreedyMHV() = default;
        void solve(std::shared_ptr<DataStructures::Graph>& graph) const override;

    private:
        static void colourAllVertices(
            std::shared_ptr<DataStructures::Graph>& graph,
            DataStructures::ColourType colour
        ) ;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GREEDYMHV_H
