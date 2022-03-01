//
// Created by louis on 18/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYMHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYMHVEVALUATOR_H

#include "Evaluator.h"

namespace DataStructures
{
    class potentialHappyMHVEvaluator : public Evaluator
    {
    private:
        const int happyVertexWeight;
        const int potentialHappyVertexWeight;
        const int unhappyVertexWeight;

    public:
        potentialHappyMHVEvaluator(
            int happyVertexWeight,
            int potentialHappyVertexWeight,
            int unhappyVertexWeight
        );

        [[nodiscard]] int evaluate(const DataStructures::Graph* graph) const override;

        [[nodiscard]] int evaluate(
            const std::set<DataStructures::VertexType>& recolouredVertices,
            std::vector<DataStructures::ColourAssignments*> oldColourAssignments,
            DataStructures::ColourAssignments* newColourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation
        ) const override;

    private:
        [[nodiscard]] int getVertexWeight(
            DataStructures::VertexType vertex,
            DataStructures::ColourAssignments* colourAssignments,
            const DataStructures::Graph* graph
        ) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_POTENTIALHAPPYMHVEVALUATOR_H
