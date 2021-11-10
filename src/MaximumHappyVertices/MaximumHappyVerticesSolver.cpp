//
// Created by louis on 25/10/2021.
//

#include "MaximumHappyVerticesSolver.h"

MaximumHappyVertices::MaximumHappyVerticesSolver::MaximumHappyVerticesSolver(
        const DataStructures::Graph& graph,
        const DataStructures::PartialColouring& partialColouring)
        : graph{graph}, partialColouring{partialColouring}
{}

unsigned int MaximumHappyVertices::MaximumHappyVerticesSolver::getNbHappyVertices(DataStructures::Colouring* colouring) const
{
    unsigned int nbHappyVertices{0};
    for (DataStructures::VertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
    {
        bool vertexIsHappy{true};
        for (DataStructures::VertexType neighbour : *graph.getNeighbours(vertex))
        {
            if (colouring->getColour(neighbour) != colouring->getColour(vertex))
            {
                vertexIsHappy = false;
                break;
            }
        }
        if (vertexIsHappy)
        {
            nbHappyVertices++;
        }
    }
    return nbHappyVertices;
}
