//
// Created by louis on 27/10/2021.
//

#include "GrowthMHV.h"

#include <algorithm>
#include <set>
#include <numeric>
#include <random>
#include <functional>


struct Comparator
{
public:
    static const DataStructures::Graph* graph;

    bool operator() (const DataStructures::VertexType& v1, const DataStructures::VertexType& v2) const
    {
        return graph->getDegree(v1) == graph->getDegree(v2) ? v1 < v2 : graph->getDegree(v1) > graph->getDegree(v2);
    }
};


const DataStructures::Graph* Comparator::graph = nullptr;
static std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> vertexTypes{};
static std::set<DataStructures::VertexType, Comparator> H_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> U_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> P_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LP_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LH_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LU_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LF_vertices(Comparator{});


DataStructures::Colouring* MaximumHappyVertices::GrowthMHV::solve(
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring) const
{
    vertexTypes.clear();
    vertexTypes.resize(graph->getNbVertices());
    Comparator::graph = graph;
    H_vertices.clear();
    U_vertices.clear();
    P_vertices.clear();
    LP_vertices.clear();
    LH_vertices.clear();
    LU_vertices.clear();
    LF_vertices.clear();

    std::deque<DataStructures::VertexType> verticesToUpdate(graph->getNbVertices());
    std::iota(verticesToUpdate.begin(), verticesToUpdate.end(), 0);
    setGrowthTypes(verticesToUpdate, graph, colouring);

    auto* solution = new DataStructures::MutableColouring{colouring};
    while (!(LP_vertices.empty() && LH_vertices.empty() && LU_vertices.empty() && LF_vertices.empty()))
    {
        if (!P_vertices.empty())
        {
            auto vertexIt{P_vertices.begin()};
            DataStructures::ColourType colour{solution->getColour(*vertexIt)};
            for (DataStructures::VertexType neighbour : *graph->getNeighbours(*vertexIt))
            {
                if (vertexTypes[neighbour] == GrowthType::LP_vertex)
                {
                    solution->setColour(neighbour, colour);
                }
            }
            verticesToUpdate = verticesAtDistance(3, *vertexIt, graph);
        }
        else if (!LH_vertices.empty())
        {
            auto vertexIt{LH_vertices.begin()};
            auto uNeighbourIt = std::find_if(
                graph->getNeighbours(*vertexIt)->begin(),
                graph->getNeighbours(*vertexIt)->end(),
                [](const DataStructures::VertexType& neighbour)
                    { return vertexTypes[neighbour] == GrowthType::U_vertex; }
            );
            DataStructures::ColourType colour{solution->getColour(*uNeighbourIt)};
            solution->setColour(*vertexIt, colour);
            for (DataStructures::VertexType neighbour : *graph->getNeighbours(*vertexIt))
            {
                if (!solution->isColoured(neighbour))
                {
                    solution->setColour(neighbour, colour);
                }
            }
            verticesToUpdate = verticesAtDistance(3, *vertexIt, graph);
        }
        else if (!LU_vertices.empty())
        {
            auto vertexIt{LU_vertices.begin()};
            auto uNeighbourIt = std::find_if(
                graph->getNeighbours(*vertexIt)->begin(),
                graph->getNeighbours(*vertexIt)->end(),
                [](const DataStructures::VertexType& neighbour)
                    { return vertexTypes[neighbour] == GrowthType::U_vertex; }
            );
            solution->setColour(*vertexIt, solution->getColour(*uNeighbourIt));

            verticesToUpdate.push_back(*vertexIt);
            for (DataStructures::VertexType neighbour : *graph->getNeighbours(*vertexIt))
                verticesToUpdate.push_back(neighbour);
        }
        else
        {
            // Only LF vertices remain to be coloured, which means they form (a) disconnected
            // component(s) and can all receive an arbitrary colour such that all of them are happy
            static std::mt19937 rng{std::random_device{}()};
            std::uniform_int_distribution<> distribution(0, colouring->getNbColours());
            DataStructures::ColourType colour = distribution(rng);
            for (DataStructures::VertexType lfVertex : LF_vertices)
                solution->setColour(lfVertex, colour);
            break;
        }

        for (DataStructures::VertexType vertex : verticesToUpdate)
        {
            switch (vertexTypes[vertex])
            {
                case GrowthType::H_vertex: H_vertices.erase(vertex); break;
                case GrowthType::U_vertex: U_vertices.erase(vertex); break;
                case GrowthType::P_vertex: P_vertices.erase(vertex);break;
                case GrowthType::LH_vertex: LH_vertices.erase(vertex); break;
                case GrowthType::LU_vertex: LU_vertices.erase(vertex); break;
                case GrowthType::LP_vertex: LP_vertices.erase(vertex); break;
                case GrowthType::LF_vertex: LF_vertices.erase(vertex); break;
                case GrowthType::TEMP_INVALID_TYPE: break;
            }
            vertexTypes[vertex] = GrowthType::TEMP_INVALID_TYPE;
        }
        setGrowthTypes(verticesToUpdate, graph, solution);
    }
    return solution;
}

void MaximumHappyVertices::GrowthMHV::setGrowthTypes(
        std::deque<DataStructures::VertexType>& verticesToUpdate,
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring)
{
    std::deque<DataStructures::VertexType> colouredVerticesToUpdate{};
    std::deque<DataStructures::VertexType> uncolouredVerticesToUpdate{};
    while (!verticesToUpdate.empty())
    {
        DataStructures::VertexType vertex{verticesToUpdate.front()};
        verticesToUpdate.pop_front();
        if (colouring->isColoured(vertex))
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
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (!colouring->isColoured(neighbour))
            {
                hasUncolouredNeighbour = true;
            }
            else if (colouring->getColour(neighbour) != colouring->getColour(vertex))
            {
                vertexIsUnhappy = true;
                break;
            }
        }

        if (vertexIsUnhappy)
        {
            U_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::U_vertex;
        }
        else if (hasUncolouredNeighbour)
        {
            P_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::P_vertex;
        }
        else
        {
            H_vertices.insert(vertex);
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
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (vertexTypes[neighbour] == GrowthType::P_vertex)
            {
                hasPNeighbour = true;
                break;
            }
            else if (colourNeighbours == 0 && colouring->isColoured(neighbour))
            {
                colourNeighbours = colouring->getColour(neighbour);
            }
            else if (colourNeighbours != 0 && colouring->isColoured(neighbour) && colouring->getColour(neighbour) != colourNeighbours)
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
                    graph->getNeighbours(vertexToCheck)->begin(),
                    graph->getNeighbours(vertexToCheck)->end()
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
