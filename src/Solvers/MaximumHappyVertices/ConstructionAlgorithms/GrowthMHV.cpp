//
// Created by louis on 27/10/2021.
//

#include "GrowthMHV.h"
#include "../../../rng.h"

#include <algorithm>
#include <set>
#include <numeric>
#include <functional>


struct Comparator
{
public:
    static const DataStructures::Graph* graph;

    bool operator()(const DataStructures::VertexType& v1, const DataStructures::VertexType& v2) const
    {
        return graph->getDegree(v1) == graph->getDegree(v2)
                    ? v1 < v2
                    : graph->getDegree(v1) > graph->getDegree(v2);
    }
};

const DataStructures::Graph* Comparator::graph = nullptr;
static std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> vertexTypes{};
static std::set<DataStructures::VertexType, Comparator> P_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LP_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LH_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LU_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LF_vertices(Comparator{});


void MaximumHappyVertices::GrowthMHV::solve(DataStructures::Graph* graph) const
{
    vertexTypes.clear();
    vertexTypes.resize(graph->getNbVertices());
    Comparator::graph = graph;
    P_vertices.clear();
    LP_vertices.clear();
    LH_vertices.clear();
    LU_vertices.clear();
    LF_vertices.clear();

    std::deque<DataStructures::VertexType> verticesToUpdate(graph->getNbVertices());
    std::iota(verticesToUpdate.begin(), verticesToUpdate.end(), 0);
    setGrowthTypes(verticesToUpdate, graph);

    while (!(LP_vertices.empty() && LH_vertices.empty() && LU_vertices.empty() && LF_vertices.empty()))
    {
        if (!P_vertices.empty())
        {
            DataStructures::VertexType p_vertex{*P_vertices.begin()};
            DataStructures::ColourType colour{graph->getColour(p_vertex)};
            for (DataStructures::VertexType neighbour : graph->getNeighbours(p_vertex))
            {
                if (vertexTypes[neighbour] == GrowthType::LP_vertex)
                {
                    graph->setColour(neighbour, colour);
                }
            }
            verticesToUpdate = verticesAtDistance(3, p_vertex, graph);
        }
        else if (!LH_vertices.empty())
        {
            DataStructures::VertexType lh_vertex{*LH_vertices.begin()};
            auto uNeighbourIt = std::find_if(
                graph->getNeighbours(lh_vertex).begin(),
                graph->getNeighbours(lh_vertex).end(),
                [](const DataStructures::VertexType& neighbour)
                    { return vertexTypes[neighbour] == GrowthType::U_vertex; }
            );
            DataStructures::ColourType colour{graph->getColour(*uNeighbourIt)};
            graph->setColour(lh_vertex, colour);
            for (DataStructures::VertexType neighbour : graph->getNeighbours(lh_vertex))
            {
                if (!graph->isColoured(neighbour))
                {
                    graph->setColour(neighbour, colour);
                }
            }
            verticesToUpdate = verticesAtDistance(3, lh_vertex, graph);
        }
        else if (!LU_vertices.empty())
        {
            DataStructures::VertexType lu_vertex{*LU_vertices.begin()};
            DataStructures::VertexType u_neighbour = *std::find_if(
                graph->getNeighbours(lu_vertex).begin(),
                graph->getNeighbours(lu_vertex).end(),
                [](const DataStructures::VertexType& neighbour)
                    { return vertexTypes[neighbour] == GrowthType::U_vertex; }
            );
            graph->setColour(lu_vertex, graph->getColour(u_neighbour));

            verticesToUpdate = verticesAtDistance(1, lu_vertex, graph);
        }
        else
        {
            std::uniform_int_distribution<> distribution(0, graph->getNbColours());
            DataStructures::VertexType lf_vertex{*LF_vertices.begin()};
            DataStructures::ColourType colour = distribution(RNG::rng);
            graph->setColour(lf_vertex, colour);
            verticesToUpdate = verticesAtDistance(1, lf_vertex, graph);
        }

        for (DataStructures::VertexType vertex : verticesToUpdate)
        {
            switch (vertexTypes[vertex])
            {
                case GrowthType::P_vertex: P_vertices.erase(vertex);break;
                case GrowthType::LH_vertex: LH_vertices.erase(vertex); break;
                case GrowthType::LU_vertex: LU_vertices.erase(vertex); break;
                case GrowthType::LP_vertex: LP_vertices.erase(vertex); break;
                case GrowthType::LF_vertex: LF_vertices.erase(vertex); break;
                default: break;
            }
            vertexTypes[vertex] = GrowthType::TEMP_INVALID_TYPE;
        }
        setGrowthTypes(verticesToUpdate, graph);
    }
}

void MaximumHappyVertices::GrowthMHV::setGrowthTypes(
        std::deque<DataStructures::VertexType>& verticesToUpdate,
        const DataStructures::Graph* graph)
{
    std::deque<DataStructures::VertexType> colouredVerticesToUpdate{};
    std::deque<DataStructures::VertexType> uncolouredVerticesToUpdate{};
    while (!verticesToUpdate.empty())
    {
        DataStructures::VertexType vertex{verticesToUpdate.front()};
        verticesToUpdate.pop_front();
        if (graph->isColoured(vertex))
            colouredVerticesToUpdate.push_back(vertex);
        else
            uncolouredVerticesToUpdate.push_back(vertex);
    }

    while (!colouredVerticesToUpdate.empty())
    {
        DataStructures::VertexType vertex{colouredVerticesToUpdate.front()};
        colouredVerticesToUpdate.pop_front();

        bool vertexIsUnhappy{false};
        bool hasUncolouredNeighbour{false};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!graph->isColoured(neighbour))
            {
                hasUncolouredNeighbour = true;
            }
            else if (graph->getColour(neighbour) != graph->getColour(vertex))
            {
                vertexIsUnhappy = true;
                break;
            }
        }

        if (vertexIsUnhappy)
        {
            vertexTypes[vertex] = GrowthType::U_vertex;
        }
        else if (hasUncolouredNeighbour)
        {
            P_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::P_vertex;
        }
        else
        {
            vertexTypes[vertex] = GrowthType::H_vertex;
        }
    }

    while (!uncolouredVerticesToUpdate.empty())
    {
        DataStructures::VertexType vertex{uncolouredVerticesToUpdate.front()};
        uncolouredVerticesToUpdate.pop_front();

        DataStructures::ColourType colourNeighbours{0};
        bool hasPNeighbour{false};
        bool isUnhappy{false};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (vertexTypes[neighbour] == GrowthType::P_vertex)
            {
                hasPNeighbour = true;
                break;
            }
            else if (colourNeighbours == 0 && graph->isColoured(neighbour))
            {
                colourNeighbours = graph->getColour(neighbour);
            }
            else if (colourNeighbours != 0 && graph->isColoured(neighbour) && graph->getColour(neighbour) != colourNeighbours)
            {
                isUnhappy = true;
            }
        }

        if (hasPNeighbour)
        {
            LP_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::LP_vertex;
        }
        else if (isUnhappy)
        {
            LU_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::LU_vertex;
        }
        else if (colourNeighbours == 0) // No neighbours have a colour
        {
            LF_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::LF_vertex;
        }
        else
        {
            LH_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::LH_vertex;
        }
    }
}

std::deque<DataStructures::VertexType> MaximumHappyVertices::GrowthMHV::verticesAtDistance(
        size_t distance,
        DataStructures::VertexType vertex,
        const DataStructures::Graph* graph)
{
    // Neighbourhood at distance 1
    std::set<DataStructures::VertexType> neighbourhood{};
    std::set<DataStructures::VertexType> verticesToCheck{vertex};

    // Neighbourhood at distance 2 to distance (distance-1)
    for (size_t currentDistance{1}; currentDistance <= distance; currentDistance++)
    {
        std::set<DataStructures::VertexType> nextVerticesToCheck(neighbourhood);
        for (DataStructures::VertexType vertexToCheck : verticesToCheck)
        {
            auto pair = neighbourhood.insert(vertexToCheck);
            if (pair.second)
            {
                nextVerticesToCheck.insert(
                    graph->getNeighbours(vertexToCheck).begin(),
                    graph->getNeighbours(vertexToCheck).end()
                );
            }
        }
        verticesToCheck = nextVerticesToCheck;
    }

    // At the last distance, you don't need to do any computations for neighbouring vertices
    for (DataStructures::VertexType vertexToCheck : verticesToCheck)
        neighbourhood.insert(vertexToCheck);

    return {neighbourhood.begin(), neighbourhood.end()};
}
