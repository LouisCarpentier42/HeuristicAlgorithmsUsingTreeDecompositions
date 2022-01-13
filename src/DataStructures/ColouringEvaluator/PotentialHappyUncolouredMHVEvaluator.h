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

        [[nodiscard]] int evaluate(const DataStructures::Graph* graph) const override;

        [[nodiscard]] int evaluate(
            const std::vector<DataStructures::VertexType>& recolouredVertices,
            const DataStructures::TableEntry::ColourAssignments& colourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation
        ) const override;

    private:
        [[nodiscard]] int getWeightColouredVertex(
            DataStructures::VertexType colouredVertex,
            const DataStructures::Graph* graph
        ) const;
        [[nodiscard]] int getWeightUncolouredVertex(
            DataStructures::VertexType uncolouredVertex,
            const DataStructures::Graph* graph
        ) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYUNCOLOUREDMHVEVALUATOR_H
