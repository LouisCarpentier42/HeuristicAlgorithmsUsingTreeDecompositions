//
// Created by louis on 27/10/2021.
//

#include "GrowthMHV.h"

#include <algorithm>

// TODO optimize the algorithm!

DataStructures::MutableColouring* MaximumHappyVertices::GrowthMHV::solve(const DataStructures::Graph* graph, const DataStructures::Colouring* colouring) const
{
    std::vector<VertexTypeMHV> types(graph->getNbVertices());
    auto* solution = new DataStructures::MutableColouring{colouring};

    updateVertexTypes(graph, solution, types);

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
            DataStructures::VertexType pVertex = std::distance(types.begin(), pVertexIterator);
            for (DataStructures::VertexType neighbour : *graph->getNeighbours(pVertex))
            {
                if (types[neighbour] == VertexTypeMHV::LP_vertex)
                {
                    solution->setColour(neighbour, solution->getColour(pVertex));
                }
            }
        }
        else
        {
            auto lhVertexIterator = std::find(types.begin(), types.end(), VertexTypeMHV::LH_vertex);
            if (lhVertexIterator != types.end())
            {
                DataStructures::VertexType lhVertex = std::distance(types.begin(), lhVertexIterator);
                DataStructures::ColourType uNeighbourColour{0};
                for (DataStructures::VertexType neighbour : *graph->getNeighbours(lhVertex))
                {
                    if (types[neighbour] == VertexTypeMHV::U_vertex)
                    {
                        uNeighbourColour = solution->getColour(neighbour);
                        break;
                    }
                }
                solution->setColour(lhVertex, uNeighbourColour);
                for (DataStructures::VertexType neighbour : *graph->getNeighbours(lhVertex))
                {
                    if (types[neighbour] == VertexTypeMHV::LH_vertex ||
                        types[neighbour] == VertexTypeMHV::LU_vertex ||
                        types[neighbour] == VertexTypeMHV::LP_vertex ||
                        types[neighbour] == VertexTypeMHV::LF_vertex)
                    {
                        solution->setColour(neighbour, uNeighbourColour);
                    }
                }
            }
            else // There must be an LU vertex
            {
                auto luVertexIterator = std::find(types.begin(), types.end(), VertexTypeMHV::LU_vertex);
                DataStructures::VertexType luVertex = std::distance(types.begin(), luVertexIterator);
                for (DataStructures::VertexType neighbour : *graph->getNeighbours(luVertex))
                {
                    if (types[neighbour] == VertexTypeMHV::U_vertex)
                    {
                        solution->setColour(luVertex, solution->getColour(neighbour));
                        break;
                    }
                }
            }
        }
        updateVertexTypes(graph, solution, types);
    }
    return solution;
}

void MaximumHappyVertices::GrowthMHV::updateVertexTypes(const DataStructures::Graph* graph, DataStructures::MutableColouring* solution, std::vector<VertexTypeMHV>& types)
{
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (solution->isColoured(vertex))
        {
            // If all of vertex's neighbours have the same colour
            if (std::all_of(
                    graph->getNeighbours(vertex)->begin(),
                    graph->getNeighbours(vertex)->end(),
                    [solution, vertexColour{solution->getColour(vertex)}](DataStructures::VertexType neighbour){return solution->getColour(neighbour) == vertexColour;} ))
                types[vertex] = VertexTypeMHV::H_vertex;
            // If any of vertex's neighbours has a different colour
            else if (std::any_of(
                    graph->getNeighbours(vertex)->begin(),
                    graph->getNeighbours(vertex)->end(),
                    [solution, vertexColour{solution->getColour(vertex)}](DataStructures::VertexType neighbour){return solution->isColoured(neighbour) && solution->getColour(neighbour) != vertexColour;} ))
                types[vertex] = VertexTypeMHV::U_vertex;
            // None of vertex's neighbours have a different colour, but not all of them have been coloured in the same colour
            else
                types[vertex] = VertexTypeMHV::P_vertex;
        }
    }

    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!solution->isColoured(vertex))
        {
            if (std::any_of(
                    graph->getNeighbours(vertex)->begin(),
                    graph->getNeighbours(vertex)->end(),
                    [types](DataStructures::VertexType neighbour){return types[neighbour] == VertexTypeMHV::P_vertex;} ))
                types[vertex] = VertexTypeMHV::LP_vertex;
            else if (std::all_of(
                    graph->getNeighbours(vertex)->begin(),
                    graph->getNeighbours(vertex)->end(),
                    [solution](DataStructures::VertexType neighbour){return !solution->isColoured(neighbour);} ))
                types[vertex] = VertexTypeMHV::LF_vertex;
            else
            {
                for (int i{0}; i < graph->getDegree(vertex); i++)
                {
                    if (solution->isColoured((*graph->getNeighbours(vertex))[i]))
                    {
                        // Check if all following neighbours either are not coloured or have the same colour
                        DataStructures::ColourType colour{solution->getColour((*graph->getNeighbours(vertex))[i])};
                        if (std::all_of(
                                graph->getNeighbours(vertex)->begin()+i,
                                graph->getNeighbours(vertex)->end(),
                                [solution, colour](DataStructures::VertexType neighbour){return !solution->isColoured(neighbour) || solution->getColour(neighbour) == colour;} ))
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
