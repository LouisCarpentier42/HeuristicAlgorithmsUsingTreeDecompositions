//
// Created by louis on 12/12/2021.
//

#include <numeric>
#include <algorithm>
#include "ConcreteJoinNodeHandlers.h"
#include "../../MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h"
#include "../../../rng.h"

struct Comparator
{
public:
    static const DataStructures::Graph* graph1; // graph1 because otherwise clashes with comparator in growthMHV

    bool operator()(const DataStructures::VertexType& v1, const DataStructures::VertexType& v2) const
    {
        return graph1->getDegree(v1) == graph1->getDegree(v2)
                    ? v1 < v2
                    : graph1->getDegree(v1) > graph1->getDegree(v2);
    }
};

const DataStructures::Graph* Comparator::graph1 = nullptr;
static std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> vertexTypes{};
static std::set<DataStructures::VertexType, Comparator> P_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LP_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LH_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LU_vertices(Comparator{});
static std::set<DataStructures::VertexType, Comparator> LF_vertices(Comparator{});


void setGrowthTypes(
        std::deque<DataStructures::VertexType>& verticesToUpdate,
        const std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::ColourAssignment>& colourAssignments,
        const std::set<DataStructures::VertexType>& verticesToColour)
{
    std::deque<DataStructures::VertexType> colouredVerticesToUpdate{};
    std::deque<DataStructures::VertexType> uncolouredVerticesToUpdate{};
    while (!verticesToUpdate.empty())
    {
        DataStructures::VertexType vertex{verticesToUpdate.front()};
        verticesToUpdate.pop_front();
        if (colourAssignments->isColoured(vertex))
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
            if (!colourAssignments->isColoured(neighbour))
            {
                hasUncolouredNeighbour = true;
            }
            else if (colourAssignments->getColour(neighbour) != colourAssignments->getColour(vertex))
            {
                vertexIsUnhappy = true;
                break;
            }
        }

        if (vertexIsUnhappy)
        {
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::U_vertex;
        }
        else if (hasUncolouredNeighbour)
        {
            if (verticesToColour.find(vertex) != verticesToColour.end())
                P_vertices.insert(vertex);
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex;
        }
        else
        {
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::H_vertex;
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
            if (vertexTypes[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex)
            {
                hasPNeighbour = true;
                break;
            }
            else if (colourNeighbours == 0 && colourAssignments->isColoured(neighbour))
            {
                colourNeighbours = colourAssignments->getColour(neighbour);
            }
            else if (colourNeighbours != 0 && colourAssignments->isColoured(neighbour) && colourAssignments->getColour(neighbour) != colourNeighbours)
            {
                isUnhappy = true;
            }
        }

        if (hasPNeighbour)
        {
            if (verticesToColour.find(vertex) != verticesToColour.end())
                LP_vertices.insert(vertex);
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::LP_vertex;
        }
        else if (isUnhappy)
        {
            if (verticesToColour.find(vertex) != verticesToColour.end())
                LU_vertices.insert(vertex);
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::LU_vertex;
        }
        else if (colourNeighbours == 0) // No neighbours have a colour
        {
            if (verticesToColour.find(vertex) != verticesToColour.end())
                LF_vertices.insert(vertex);
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::LF_vertex;
        }
        else
        {
            if (verticesToColour.find(vertex) != verticesToColour.end())
                LH_vertices.insert(vertex);
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::LH_vertex;
        }
    }
}

std::deque<DataStructures::VertexType> verticesAtDistance(
        size_t distance,
        DataStructures::VertexType vertex,
        const std::shared_ptr<DataStructures::Graph>& graph)
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

Solvers::GrowthColourBagJoinNodeHandler::GrowthColourBagJoinNodeHandler(
        std::shared_ptr<const EvaluationMerger>& evaluationMerger,
        double percentMustBeEqual)
    : PairwiseCombineJoinHandler{evaluationMerger, percentMustBeEqual}
{ }

void Solvers::GrowthColourBagJoinNodeHandler::addMergedEntries(
        std::shared_ptr<DataStructures::JoinNode>& node,
        const std::shared_ptr<DataStructures::TableEntry>& leftEntry,
        const std::shared_ptr<DataStructures::TableEntry>& rightEntry) const
{
    // The colour assignments used to construct a new assignment
    std::vector<std::shared_ptr<DataStructures::ColourAssignment>> oldColourAssignments{leftEntry->getColourAssignments(), rightEntry->getColourAssignments()};

    // Reset the types
    vertexTypes.clear();
    vertexTypes.resize(graph->getNbVertices());
    Comparator::graph1 = graph.get();
    P_vertices.clear();
    LP_vertices.clear();
    LH_vertices.clear();
    LU_vertices.clear();
    LF_vertices.clear();

    // Create a colour assignment
    std::shared_ptr<DataStructures::ColourAssignment> leftEntryAssignments = leftEntry->getColourAssignments();
    std::shared_ptr<DataStructures::ColourAssignment> rightEntryAssignments = rightEntry->getColourAssignments();
    std::shared_ptr<DataStructures::ColourAssignment> assignments = std::make_shared<DataStructures::ColourAssignment>
    (
        node,
        leftEntryAssignments,
        rightEntryAssignments
    );
    for (DataStructures::VertexType vertex : verticesToColour)
        assignments->removeColour(vertex);

    std::deque<DataStructures::VertexType> verticesToUpdate(graph->getNbVertices());
    std::iota(verticesToUpdate.begin(), verticesToUpdate.end(), 0);
    setGrowthTypes(verticesToUpdate, graph, assignments, verticesToColour);
    while (!(LP_vertices.empty() && LH_vertices.empty() && LU_vertices.empty() && LF_vertices.empty()))
    {
        if (!P_vertices.empty())
        {
            DataStructures::VertexType p_vertex{*P_vertices.begin()};
            DataStructures::ColourType colour{assignments->getColour(p_vertex)};
            for (DataStructures::VertexType neighbour : graph->getNeighbours(p_vertex))
            {
                if (vertexTypes[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::LP_vertex)
                {
                    assignments->assignColour(neighbour, colour);
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
                    { return vertexTypes[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::U_vertex; }
                );
            DataStructures::ColourType colour{assignments->getColour(*uNeighbourIt)};
            assignments->assignColour(lh_vertex, colour);
            for (DataStructures::VertexType neighbour : graph->getNeighbours(lh_vertex))
            {
                if (!assignments->isColoured(neighbour))
                {
                    assignments->assignColour(neighbour, colour);
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
                    { return vertexTypes[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::U_vertex; }
                );
            assignments->assignColour(lu_vertex, assignments->getColour(u_neighbour));

            verticesToUpdate = verticesAtDistance(1, lu_vertex, graph);
        }
        else
        {
            std::uniform_int_distribution<> distribution(0, graph->getNbColours());
            DataStructures::VertexType lf_vertex{*LF_vertices.begin()};
            DataStructures::ColourType colour = distribution(RNG::rng);
            assignments->assignColour(lf_vertex, colour);
            verticesToUpdate = verticesAtDistance(1, lf_vertex, graph);
        }

        for (DataStructures::VertexType vertex : verticesToUpdate)
        {
            switch (vertexTypes[vertex])
            {
                case MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex: P_vertices.erase(vertex);break;
                case MaximumHappyVertices::GrowthMHV::GrowthType::LH_vertex: LH_vertices.erase(vertex); break;
                case MaximumHappyVertices::GrowthMHV::GrowthType::LU_vertex: LU_vertices.erase(vertex); break;
                case MaximumHappyVertices::GrowthMHV::GrowthType::LP_vertex: LP_vertices.erase(vertex); break;
                case MaximumHappyVertices::GrowthMHV::GrowthType::LF_vertex: LF_vertices.erase(vertex); break;
                default: break;
            }
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::TEMP_INVALID_TYPE;
        }
        setGrowthTypes(verticesToUpdate, graph, assignments, verticesToColour);
    }

    // Add a new entry to the table
    std::shared_ptr<DataStructures::TableEntry> newEntry = std::make_shared<DataStructures::TableEntry>(
            evaluator->evaluate(node->getBagContent(), oldColourAssignments, assignments, graph, evaluationMerger->mergeEvaluations(leftEntry->getEvaluation(), rightEntry->getEvaluation())),
            assignments
        );
    node->getTable().push(newEntry);
}


