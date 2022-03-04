//
// Created by louis on 06/02/2022.
//

#include "ExactTreeDecompositionRankingMHV.h"
#include <algorithm>

void Solvers::ExactTreeDecompositionRankingMHV::addSolution(
        int evaluation,
        const DataStructures::ColourAssignments& colourAssignments,
        const DataStructures::HappyVerticesAssignments& happyVerticesAssignments)
{
    solutions.insert({{colourAssignments, happyVerticesAssignments}, evaluation});
}

int Solvers::ExactTreeDecompositionRankingMHV::getBestEvaluation()
{
    return std::max_element(solutions.begin(), solutions.end(), [](auto& s1, auto& s2) { return s1.second < s2.second; })->second;
}

int Solvers::ExactTreeDecompositionRankingMHV::getEvaluation(
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

const DataStructures::ColourAssignments& Solvers::ExactTreeDecompositionRankingMHV::getConcreteAssignment(
        const DataStructures::ColourAssignments& colourAssignments,
        const DataStructures::HappyVerticesAssignments& happyVerticesAssignments) const
{
    return solutions.find({colourAssignments, happyVerticesAssignments})->first.first;
}

Solvers::ExactTreeDecompositionRankingMHV::ExactTreeDecompositionRankingIterator Solvers::ExactTreeDecompositionRankingMHV::begin() const
{
    return solutions.begin();
}

Solvers::ExactTreeDecompositionRankingMHV::ExactTreeDecompositionRankingIterator Solvers::ExactTreeDecompositionRankingMHV::end() const
{
    return solutions.end();
}
