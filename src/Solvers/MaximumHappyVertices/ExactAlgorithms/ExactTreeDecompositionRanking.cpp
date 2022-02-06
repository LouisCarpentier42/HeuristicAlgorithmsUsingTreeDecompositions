//
// Created by louis on 06/02/2022.
//

#include "ExactTreeDecompositionRanking.h"

void MaximumHappyVertices::ExactTreeDecompositionRanking::addSolution(
        int evaluation,
        const DataStructures::ColourAssignments& colourAssignments,
        const DataStructures::HappyVerticesAssignments& happyVerticesAssignments)
{
    solutions.insert({{colourAssignments, happyVerticesAssignments}, evaluation});
}

int MaximumHappyVertices::ExactTreeDecompositionRanking::getEvaluation(
        const DataStructures::ColourAssignments& colourAssignments,
        const DataStructures::HappyVerticesAssignments& happyVerticesAssignments) const
{
    try {
        return solutions.at({colourAssignments, happyVerticesAssignments});
    }
    catch(std::out_of_range& e) {
        return NEGATIVE_INFINITY;
    }
}

MaximumHappyVertices::ExactTreeDecompositionRanking::ExactTreeDecompositionRankingIterator MaximumHappyVertices::ExactTreeDecompositionRanking::begin() const
{
    return solutions.begin();
}

MaximumHappyVertices::ExactTreeDecompositionRanking::ExactTreeDecompositionRankingIterator MaximumHappyVertices::ExactTreeDecompositionRanking::end() const
{
    return solutions.end();
}
