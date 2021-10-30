//
// Created by louis on 27/10/2021.
//

#include "GrowthMHV.h"

#include <algorithm>

MaximumHappyVertices::GrowthMHV::GrowthMHV(
        const DataStructures::Graph& graph,
        const MaximumHappyVertices::PartialColouring& partialColouring)
        : MaximumHappyVerticesSolver(graph, partialColouring)
{}

MaximumHappyVertices::Colouring* MaximumHappyVertices::GrowthMHV::solve() const
{
    std::vector<VertexTypeMHV> types(graph.getNbVertices());
    auto* colouring = new Colouring{partialColouring};

    updateVertexTypes(colouring, types);

    while (std::any_of(
            types.begin(),
            types.end(),
            [](VertexTypeMHV type) {
                return type == VertexTypeMHV::LH_vertex ||
                       type == VertexTypeMHV::LU_vertex ||
                       type == VertexTypeMHV::LP_vertex ||
                       type == VertexTypeMHV::LF_vertex;
                }
            ))
    {
        auto pVertexIterator = std::find(types.begin(), types.end(), VertexTypeMHV::P_vertex);
        if (pVertexIterator != types.end())
        {
            vertexType pVertex = std::distance(types.begin(), pVertexIterator);
            for (vertexType neighbour : *graph.getNeighbours(pVertex))
            {
                if (types[neighbour] == VertexTypeMHV::LP_vertex)
                {
                    colouring->setColour(neighbour, colouring->getColour(pVertex));
                }
            }
        }
        else
        {
            auto lhVertexIterator = std::find(types.begin(), types.end(), VertexTypeMHV::LH_vertex);
            if (lhVertexIterator != types.end())
            {
                vertexType lhVertex = std::distance(types.begin(), lhVertexIterator);
                colourType uNeighbourColour{0};
                for (vertexType neighbour : *graph.getNeighbours(lhVertex))
                {
                    if (types[neighbour] == VertexTypeMHV::U_vertex)
                    {
                        uNeighbourColour = colouring->getColour(neighbour);
                        break;
                    }
                }
                colouring->setColour(lhVertex, uNeighbourColour);
                for (vertexType neighbour : *graph.getNeighbours(lhVertex))
                {
                    if (types[neighbour] == VertexTypeMHV::LH_vertex ||
                        types[neighbour] == VertexTypeMHV::LU_vertex ||
                        types[neighbour] == VertexTypeMHV::LP_vertex ||
                        types[neighbour] == VertexTypeMHV::LF_vertex)
                    {
                        colouring->setColour(neighbour, uNeighbourColour);
                    }
                }
            }
            else // There must be an LU vertex
            {
                auto luVertexIterator = std::find(types.begin(), types.end(), VertexTypeMHV::LU_vertex);
                vertexType luVertex = std::distance(types.begin(), luVertexIterator);
                for (vertexType neighbour : *graph.getNeighbours(luVertex))
                {
                    if (types[neighbour] == VertexTypeMHV::U_vertex)
                    {
                        colouring->setColour(luVertex, colouring->getColour(neighbour));
                        break;
                    }
                }
            }
        }
        updateVertexTypes(colouring, types);
    }
    std::cout << getNbHappyVertices(colouring) << '\n'; // TODO remove
    return colouring;
}

void MaximumHappyVertices::GrowthMHV::updateVertexTypes(Colouring* colouring, std::vector<VertexTypeMHV>& types) const
{
    for (vertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
    {
        if (colouring->isColoured(vertex))
        {
            // If all of vertex's neighbours have the same colour
            if (std::all_of(
                    graph.getNeighbours(vertex)->begin(),
                    graph.getNeighbours(vertex)->end(),
                    [colouring, vertexColour{colouring->getColour(vertex)}](vertexType neighbour){return colouring->getColour(neighbour) == vertexColour;} ))
                types[vertex] = VertexTypeMHV::H_vertex;
            // If any of vertex's neighbours has a different colour
            else if (std::any_of(
                    graph.getNeighbours(vertex)->begin(),
                    graph.getNeighbours(vertex)->end(),
                    [colouring, vertexColour{colouring->getColour(vertex)}](vertexType neighbour){return colouring->isColoured(neighbour) && colouring->getColour(neighbour) != vertexColour;} ))
                types[vertex] = VertexTypeMHV::U_vertex;
            // None of vertex's neighbours have a different colour, but not all of them have been coloured in the same colour
            else
                types[vertex] = VertexTypeMHV::P_vertex;
        }
    }

    for (vertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
    {
        if (!colouring->isColoured(vertex))
        {
            if (std::any_of(
                    graph.getNeighbours(vertex)->begin(),
                    graph.getNeighbours(vertex)->end(),
                    [types](vertexType neighbour){return types[neighbour] == VertexTypeMHV::P_vertex;} ))
                types[vertex] = VertexTypeMHV::LP_vertex;
            else if (std::all_of(
                    graph.getNeighbours(vertex)->begin(),
                    graph.getNeighbours(vertex)->end(),
                    [colouring](vertexType neighbour){return !colouring->isColoured(neighbour);} ))
                types[vertex] = VertexTypeMHV::LF_vertex;
            else
            {
                for (int i{0}; i < graph.getDegree(vertex); i++)
                {
                    if (colouring->isColoured((*graph.getNeighbours(vertex))[i]))
                    {
                        // Check if all following neighbours either are not coloured or have the same colour
                        colourType colour{colouring->getColour((*graph.getNeighbours(vertex))[i])};
                        if (std::all_of(
                                graph.getNeighbours(vertex)->begin()+i,
                                graph.getNeighbours(vertex)->end(),
                                [colouring, colour](vertexType neighbour){return !colouring->isColoured(neighbour) || colouring->getColour(neighbour) == colour;} ))
                            types[vertex] = VertexTypeMHV::LH_vertex;
                        else
                            types[vertex] = VertexTypeMHV::LU_vertex;
                        break;
                    }
                }
            }
        }
    }
}
