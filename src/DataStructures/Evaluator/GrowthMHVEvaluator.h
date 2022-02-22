//
// Created by louis on 10/12/2021.
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

        [[nodiscard]] int evaluate(const DataStructures::Graph* graph) const override;

        [[nodiscard]] int evaluate(
            const std::vector<DataStructures::VertexType>& recolouredVertices,
            const std::vector<DataStructures::ColourAssignments>& oldColourAssignments,
            const DataStructures::ColourAssignments& newColourAssignments,
            const DataStructures::Graph* graph,
            int startEvaluation
        ) const override;


    private:
        [[nodiscard]] static std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> getGrowthMHVTypes(
            const std::set<DataStructures::VertexType>& vertices,
            const DataStructures::ColourAssignments& colourAssignments,
            const DataStructures::Graph* graph
        );
        [[nodiscard]] int getVertexWeight(
            const MaximumHappyVertices::GrowthMHV::GrowthType& growthType
        ) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHVEVALUATOR_H
