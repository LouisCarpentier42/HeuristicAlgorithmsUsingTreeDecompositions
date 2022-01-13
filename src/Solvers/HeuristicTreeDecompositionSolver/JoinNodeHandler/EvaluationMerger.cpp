//
// Created by louis on 11/01/2022.
//

#include "EvaluationMerger.h"

#include <algorithm>

int Solvers::AverageEvaluationMerger::mergeEvaluations(int evaluation1, int evaluation2) const
{
    return (evaluation1 + evaluation2)/2;
}

int Solvers::MaximumEvaluationMerger::mergeEvaluations(int evaluation1, int evaluation2) const
{
    return std::max(evaluation1, evaluation2);
}

int Solvers::MinimumEvaluationMerger::mergeEvaluations(int evaluation1, int evaluation2) const
{
    return std::min(evaluation1, evaluation2);
}
