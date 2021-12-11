//
// Created by louis on 27/10/2021.
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
        [[nodiscard]] DataStructures::Colouring* solve(
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring
        ) const override;

    public: // TODO set private
        static void setGrowthTypes(
            std::deque<DataStructures::VertexType>& verticesToUpdate,
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring
        );
        static void updateVertexTypes(
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring,
            std::vector<GrowthType>& types
        );
        [[nodiscard]] static std::deque<DataStructures::VertexType> verticesAtDistance(
            size_t distance,
            DataStructures::VertexType vertex,
            const DataStructures::Graph* graph
        );
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H
