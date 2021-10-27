//
// Created by louis on 27/10/2021.
//

#include "GrowthMHV.h"

#include <algorithm>

enum class VertexTypeMHV {
    H_vertex,
    U_vertex,
    P_vertex,
    LH_vertex,
    LU_vertex,
    LP_vertex,
    LF_vertex
};

MaximumHappyVertices::GrowthMHV::GrowthMHV(
        const DataStructures::Graph& graph,
        const MaximumHappyVertices::PartialColouring& partialColouring)
        : MaximumHappyVerticesSolver(graph, partialColouring)
{}

MaximumHappyVertices::Colouring* MaximumHappyVertices::GrowthMHV::solve() const
{
    std::vector<VertexTypeMHV> types(graph.getNbVertices());
    for (vertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
    {
        if (partialColouring.isColoured(vertex))
        {
            // If all of vertex's neighbours have the same colour
            if (std::all_of(
                    graph.getNeighbours(vertex)->begin(),
                    graph.getNeighbours(vertex)->end(),
                    [this, vertexColour{partialColouring.getColour(vertex)}](vertexType neighbour){return partialColouring.getColour(neighbour) == vertexColour;} ))
                types[vertex] = VertexTypeMHV::H_vertex;
            // If any of vertex's neighbours has a different colour
            else if (std::any_of(
                    graph.getNeighbours(vertex)->begin(),
                    graph.getNeighbours(vertex)->end(),
                    [this, vertexColour{partialColouring.getColour(vertex)}](vertexType neighbour){return partialColouring.getColour(neighbour) != vertexColour;} ))
                types[vertex] = VertexTypeMHV::U_vertex;
            // None of vertex's neighbours have a different colour, but not all of them have been coloured in the same colour
            else
                types[vertex] = VertexTypeMHV::P_vertex;
        }
    }

    for (vertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
    {
        if (!partialColouring.isColoured(vertex))
        {
            if (std::any_of(
                    graph.getNeighbours(vertex)->begin(),
                    graph.getNeighbours(vertex)->end(),
                    [types](vertexType neighbour){return types[neighbour] == VertexTypeMHV::P_vertex;} ))
                types[vertex] = VertexTypeMHV::LP_vertex;
            else if (std::all_of(
                    graph.getNeighbours(vertex)->begin(),
                    graph.getNeighbours(vertex)->end(),
                    [this](vertexType neighbour){return !partialColouring.isColoured(neighbour);} ))
                types[vertex] = VertexTypeMHV::LF_vertex;
            else
            {
                for (int i{0}; i < graph.getDegree(vertex); i++)
                {
                    if (partialColouring.isColoured((*graph.getNeighbours(vertex))[i]))
                    {
                        // Check if all following neighbours either are not coloured or have the same colour
                        colourType colour{partialColouring.getColour((*graph.getNeighbours(vertex))[i])};
                        if (std::all_of(
                                graph.getNeighbours(vertex)->begin()+i,
                                graph.getNeighbours(vertex)->end(),
                                [this, colour](vertexType neighbour){return !partialColouring.isColoured(neighbour) || partialColouring.getColour(neighbour) == colour;} ))
                            types[vertex] = VertexTypeMHV::LH_vertex;
                        else
                            types[vertex] = VertexTypeMHV::LU_vertex;
                        break;
                    }
                }
            }
        }
    }

    auto* colouring = new Colouring{partialColouring};

    // TODO effective algorithm

    return colouring;
}
