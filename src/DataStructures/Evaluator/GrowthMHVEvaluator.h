//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHVEVALUATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHVEVALUATOR_H

#include "Evaluator.h"
#include "../../Solvers/MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h"


namespace DataStructures
{
    class GrowthMHVEvaluator : public Evaluator
    {
    private:
        const int HWeight;
        const int UWeight;
        const int PWeight;
        const int LPWeight;
        const int LHWeight;
        const int LUWeight;
        const int LFWeight;

    public:
        GrowthMHVEvaluator(
            int HWeight,
            int UWeight,
            int PWeight,
            int LPWeight,
            int LHWeight,
            int LUWeight,
            int LFWeight
        );

        [[nodiscard]] int evaluate(const std::shared_ptr<Graph>& graph) const override;

        [[nodiscard]] int evaluate(
            const std::set<VertexType>& recolouredVertices,
            std::vector<std::shared_ptr<ColourAssignment>>& oldColourAssignments,
            std::shared_ptr<ColourAssignment>& newColourAssignment,
            const std::shared_ptr<Graph>& graph,
            int startEvaluation
        ) const override;


    private:
        [[nodiscard]] static std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> getGrowthMHVTypes(
            const std::set<VertexType>& vertices,
            std::shared_ptr<ColourAssignment>& colourAssignment,
            const std::shared_ptr<Graph>& graph
        );
        [[nodiscard]] int getVertexWeight(
            const MaximumHappyVertices::GrowthMHV::GrowthType& growthType
        ) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHVEVALUATOR_H
