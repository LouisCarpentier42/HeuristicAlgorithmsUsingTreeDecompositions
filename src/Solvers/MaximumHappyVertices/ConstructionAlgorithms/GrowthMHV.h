//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H

#include "../MaximumHappyVerticesSolver.h"

#include <deque>

namespace MaximumHappyVertices
{
    class GrowthMHV : public MaximumHappyVerticesSolver
    {
    public:
        enum class GrowthType {
            TEMP_INVALID_TYPE,
            H_vertex,
            U_vertex,
            P_vertex,
            LH_vertex,
            LU_vertex,
            LP_vertex,
            LF_vertex
        };

        GrowthMHV() = default;
        void solve(std::shared_ptr<DataStructures::Graph>& graph) const override;

    private:
        static void setGrowthTypes(
            std::deque<DataStructures::VertexType>& verticesToUpdate,
            const std::shared_ptr<DataStructures::Graph>& graph
        );
        [[nodiscard]] static std::deque<DataStructures::VertexType> verticesAtDistance(
            size_t distance,
            DataStructures::VertexType vertex,
            const std::shared_ptr<DataStructures::Graph>& graph
        );
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H
