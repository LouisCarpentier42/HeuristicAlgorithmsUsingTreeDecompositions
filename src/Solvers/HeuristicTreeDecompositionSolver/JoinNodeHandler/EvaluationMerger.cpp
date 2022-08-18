//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
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

int Solvers::SumEvaluationMerger::mergeEvaluations(int evaluation1, int evaluation2) const
{
    return evaluation1 + evaluation2;
}

int Solvers::ProductEvaluationMerger::mergeEvaluations(int evaluation1, int evaluation2) const
{
    return evaluation1 * evaluation2;
}
