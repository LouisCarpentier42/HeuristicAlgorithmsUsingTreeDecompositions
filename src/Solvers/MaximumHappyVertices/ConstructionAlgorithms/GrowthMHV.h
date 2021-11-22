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

    class GrowthMHV : public MaximumHappyVerticesSolver
    {
    public:
        GrowthMHV(const DataStructures::Graph* graph, const DataStructures::Colouring* colouring);
        [[nodiscard]] DataStructures::MutableColouring* solve() const override;

    private:
        void updateVertexTypes(DataStructures::MutableColouring* solution, std::vector<VertexTypeMHV>& types) const;
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GROWTHMHV_H