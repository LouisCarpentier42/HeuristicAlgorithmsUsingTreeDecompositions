//
// Created by louis on 10/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYUNCOLOUREDMHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYUNCOLOUREDMHVEVALUATOR_H

#include "ColouringEvaluator.h"

namespace DataStructures
{
    class PotentialHappyUncolouredMHVEvaluator : public ColouringEvaluator
    {
    private:
        const int happyColouredVertexWeight;
        const int happyUncolouredVertexWeight;
        const int potentiallyHappyColouredVertexWeight;
        const int potentiallyHappyUncolouredVertexWeight;
        const int unhappyColouredVertexWeight;
        const int unhappyUncolouredVertexWeight;

    public:
        PotentialHappyUncolouredMHVEvaluator(
            int happyColouredVertexWeight,
            int happyUncolouredVertexWeight,
            int potentiallyHappyColouredVertexWeight,
            int potentiallyHappyUncolouredVertexWeight,
            int unhappyColouredVertexWeight,
            int unhappyUncolouredVertexWeight
        );

        [[nodiscard]] int evaluate(
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring
        ) const override;

    private:
        [[nodiscard]] int getWeightColouredVertex(
            const VertexType colouredVertex,
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring
        ) const;
        [[nodiscard]] int getWeightUncolouredVertex(
            const VertexType uncolouredVertex,
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring
        ) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYUNCOLOUREDMHVEVALUATOR_H
