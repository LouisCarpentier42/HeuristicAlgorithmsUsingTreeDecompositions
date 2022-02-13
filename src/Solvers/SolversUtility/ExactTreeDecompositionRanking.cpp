//
// Created by louis on 06/02/2022.
//

#include "ExactTreeDecompositionRanking.h"
#include <algorithm>

void Solvers::ExactTreeDecompositionRanking::addSolution(
        int evaluation,
        const DataStructures::ColourAssignments& colourAssignments,
        const DataStructures::HappyVerticesAssignments& happyVerticesAssignments)
{
    solutions.insert({{colourAssignments, happyVerticesAssignments}, evaluation});
}

int Solvers::ExactTreeDecompositionRanking::getBestEvaluation()
{
    return std::max_element(solutions.begin(), solutions.end(), [](auto& s1, auto& s2) { return s1.second < s2.second; })->second;
}

int Solvers::ExactTreeDecompositionRanking::getEvaluation(
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

Solvers::ExactTreeDecompositionRanking::ExactTreeDecompositionRankingIterator Solvers::ExactTreeDecompositionRanking::begin() const
{
    return solutions.begin();
}

Solvers::ExactTreeDecompositionRanking::ExactTreeDecompositionRankingIterator Solvers::ExactTreeDecompositionRanking::end() const
{
    return solutions.end();
}
