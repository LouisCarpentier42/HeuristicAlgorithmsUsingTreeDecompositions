//
// Created by louis on 06/02/2022.
//

#include "ExactTreeDecompositionRankingMHV.h"
#include <algorithm>

void Solvers::ExactTreeDecompositionRankingMHV::addSolution(
        int evaluation,
        const DataStructures::ColourAssignment& colourAssignments,
        const DataStructures::HappyVerticesAssignments& happyVerticesAssignments,
        const std::vector<std::shared_ptr<DataStructures::ColourAssignment>>& previousFullColourings)
{
    // Create a full colouring
    auto fullColouring = std::make_shared<DataStructures::ColourAssignment>(colourAssignments.getSize());
    for (DataStructures::VertexType vertex{0}; vertex < fullColouring->getSize(); vertex++)
    {
        if (colourAssignments.isColoured(vertex))
            fullColouring->assignColour(vertex, colourAssignments.getColour(vertex));
    }

    // Assign the colours of the previous full colourings (without overriding)
    for (const std::shared_ptr<DataStructures::ColourAssignment>& previousFullColouring : previousFullColourings)
    {
        for (DataStructures::VertexType vertex{0}; vertex < fullColouring->getSize(); vertex++)
        {
            if (!fullColouring->isColoured(vertex) && previousFullColouring->isColoured(vertex) && !colourAssignments.isColoured(vertex))
                fullColouring->assignColour(vertex, previousFullColouring->getColour(vertex));
        }
    }

    // Insert the entry
    solutions.insert({
        {colourAssignments, happyVerticesAssignments},
        {evaluation, fullColouring}
    });
}

Solvers::ExactTreeDecompositionRankingMHV::ExactTreeDecompositionRankingEntry Solvers::ExactTreeDecompositionRankingMHV::getBestEntry() const
{
    return *std::max_element(solutions.begin(), solutions.end(), [](auto& s1, auto& s2) { return s1.second < s2.second; });
}

int Solvers::ExactTreeDecompositionRankingMHV::getBestEvaluation() const
{
    return getBestEntry().second.first;
}

std::shared_ptr<DataStructures::ColourAssignment> Solvers::ExactTreeDecompositionRankingMHV::getBestFullColouring() const
{
    return getBestEntry().second.second;
}

int Solvers::ExactTreeDecompositionRankingMHV::getEvaluation(
        const DataStructures::ColourAssignment& colourAssignments,
        const DataStructures::HappyVerticesAssignments& happyVerticesAssignments) const
{
    try {
        return solutions.at({colourAssignments, happyVerticesAssignments}).first;
    }
    catch(std::out_of_range& e) {
        return NEGATIVE_INFINITY;
    }
}

std::shared_ptr<DataStructures::ColourAssignment> Solvers::ExactTreeDecompositionRankingMHV::getFullColouring(
        const DataStructures::ColourAssignment& colourAssignments,
        const DataStructures::HappyVerticesAssignments& happyVerticesAssignments) const
{
    return solutions.at({colourAssignments, happyVerticesAssignments}).second;
}

Solvers::ExactTreeDecompositionRankingMHV::ExactTreeDecompositionRankingIterator Solvers::ExactTreeDecompositionRankingMHV::begin() const
{
    return solutions.begin();
}

Solvers::ExactTreeDecompositionRankingMHV::ExactTreeDecompositionRankingIterator Solvers::ExactTreeDecompositionRankingMHV::end() const
{
    return solutions.end();
}
//
//Solvers::ExactTreeDecompositionRankingMHV::~ExactTreeDecompositionRankingMHV()
//{
//
//}
