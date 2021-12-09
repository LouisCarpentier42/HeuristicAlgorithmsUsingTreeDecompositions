//
// Created by louis on 27/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H

#include "../MaximumHappyVerticesSolver.h"

namespace MaximumHappyVertices
{
    enum class VertexTypeMHV {
        H_vertex,
        U_vertex,
        P_vertex,
        LH_vertex,
        LU_vertex,
        LP_vertex,
        LF_vertex
    };

    class GrowthMHV : public MaximumHappyVerticesSolver // TODO comments
    {
    public:
        GrowthMHV() = default;
//        GrowthMHV(const DataStructures::Graph* graph, const DataStructures::Colouring* colouring);
        [[nodiscard]] DataStructures::MutableColouring* solve(
            const DataStructures::Graph* graph,
            const DataStructures::Colouring* colouring
        ) const override;

    private:
//        static void updateVertexTypes(
//                DataStructures::MutableColouring* solution,
//                std::vector<VertexTypeMHV>& types
//        );
        static void updateVertexTypes(
            const DataStructures::Graph* graph,
            DataStructures::MutableColouring* solution,
            std::vector<VertexTypeMHV>& types
        );
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H
