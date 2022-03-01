//
// Created by louis on 10/12/2021.
//

#include <numeric>
#include "GrowthMHVEvaluator.h"

DataStructures::GrowthMHVEvaluator::GrowthMHVEvaluator(
        int HWeight,
        int UWeight,
        int PWeight,
        int LPWeight,
        int LHWeight,
        int LUWeight,
        int LFWeight)
    : HWeight{HWeight},
      UWeight{UWeight},
      PWeight{PWeight},
      LPWeight{LPWeight},
      LHWeight{LHWeight},
      LUWeight{LUWeight},
      LFWeight{LFWeight}
{ }

int DataStructures::GrowthMHVEvaluator::evaluate(const DataStructures::Graph* graph) const
{
    int evaluation{0};

    std::set<DataStructures::VertexType> allVertices{};
    auto* colourAssignments = new DataStructures::ColourAssignments{graph};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        allVertices.emplace_hint(allVertices.end(), vertex);
        colourAssignments->assignColour(vertex, graph->getColour(vertex));
    }
    std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> vertexTypes = getGrowthMHVTypes(
            allVertices, colourAssignments, graph);

    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        evaluation += getVertexWeight(vertexTypes[vertex]);
    }
    return evaluation;
}

int DataStructures::GrowthMHVEvaluator::evaluate(
        const std::set<DataStructures::VertexType>& recolouredVertices,
        std::vector<DataStructures::ColourAssignments*> oldColourAssignments,
        DataStructures::ColourAssignments* newColourAssignments,
        const DataStructures::Graph* graph,
        int startEvaluation) const
{
    int evaluation{startEvaluation};
    std::set<DataStructures::VertexType> potentiallyChangedVertices = verticesAtDistance(4, recolouredVertices, graph);

    // Compute the types of the vertices that can have potentially a different type
    std::vector<std::vector<MaximumHappyVertices::GrowthMHV::GrowthType>> oldTypes{};
    oldTypes.reserve(oldColourAssignments.size());
    for (DataStructures::ColourAssignments* oldColourAssignment : oldColourAssignments)
        oldTypes.emplace_back(getGrowthMHVTypes(potentiallyChangedVertices, oldColourAssignment, graph));

    std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> newTypes = getGrowthMHVTypes(
            potentiallyChangedVertices, newColourAssignments, graph);

    // Check for all vertices how their happiness has changed
    for (DataStructures::VertexType vertex : potentiallyChangedVertices)
    {
        // Remove the evaluation from the old colour assignment
        for (const std::vector<MaximumHappyVertices::GrowthMHV::GrowthType>& vertexTypes : oldTypes)
            evaluation -= getVertexWeight(vertexTypes[vertex]);

        // Add the evaluation from the new colour assignment
        evaluation += getVertexWeight(newTypes[vertex]);
    }

    return evaluation;
}

std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> DataStructures::GrowthMHVEvaluator::getGrowthMHVTypes(
        const std::set<DataStructures::VertexType>& vertices,
        DataStructures::ColourAssignments* colourAssignments,
        const DataStructures::Graph* graph)
{
    std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> vertexTypes(
        graph->getNbVertices(),
        MaximumHappyVertices::GrowthMHV::GrowthType::TEMP_INVALID_TYPE
    );

    std::deque<DataStructures::VertexType> colouredVertices{};
    std::deque<DataStructures::VertexType> uncolouredVertices{};
    for (DataStructures::VertexType vertex : vertices)
    {
        if (colourAssignments->isColoured(vertex))
            colouredVertices.push_back(vertex);
        else
            uncolouredVertices.push_back(vertex);
    }

    while (!colouredVertices.empty())
    {
        DataStructures::VertexType vertex{colouredVertices.front()};
        colouredVertices.pop_front();

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
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex;
        }
        else
        {
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::H_vertex;
        }
    }

    while (!uncolouredVertices.empty())
    {
        DataStructures::VertexType vertex{uncolouredVertices.front()};
        uncolouredVertices.pop_front();

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
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::LP_vertex;
        }
        else if (isUnhappy)
        {
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::LU_vertex;
        }
        else if (colourNeighbours == 0) // No neighbours have a colour
        {
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::LF_vertex;
        }
        else
        {
            vertexTypes[vertex] = MaximumHappyVertices::GrowthMHV::GrowthType::LH_vertex;
        }
    }

    return vertexTypes;
}

int DataStructures::GrowthMHVEvaluator::getVertexWeight(const MaximumHappyVertices::GrowthMHV::GrowthType& growthType) const
{
    switch(growthType)
    {
        case MaximumHappyVertices::GrowthMHV::GrowthType::H_vertex: return HWeight;
        case MaximumHappyVertices::GrowthMHV::GrowthType::U_vertex: return UWeight;
        case MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex: return PWeight;
        case MaximumHappyVertices::GrowthMHV::GrowthType::LH_vertex: return LHWeight;
        case MaximumHappyVertices::GrowthMHV::GrowthType::LU_vertex: return LUWeight;
        case MaximumHappyVertices::GrowthMHV::GrowthType::LP_vertex: return LPWeight;
        case MaximumHappyVertices::GrowthMHV::GrowthType::LF_vertex: return LFWeight;
        case MaximumHappyVertices::GrowthMHV::GrowthType::TEMP_INVALID_TYPE: return 0;
    }
}

