//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EVALUATIONMERGER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EVALUATIONMERGER_H

namespace Solvers
{
    class EvaluationMerger
    {
    public:
        [[nodiscard]] virtual int mergeEvaluations(int evaluation1, int evaluation2) const = 0;
    };

    class AverageEvaluationMerger : public EvaluationMerger
    {
    public:
        [[nodiscard]] int mergeEvaluations(int evaluation1, int evaluation2) const override;
    };

    class MaximumEvaluationMerger : public EvaluationMerger
    {
    public:
        [[nodiscard]] int mergeEvaluations(int evaluation1, int evaluation2) const override;
    };

    class MinimumEvaluationMerger : public EvaluationMerger
    {
    public:
        [[nodiscard]] int mergeEvaluations(int evaluation1, int evaluation2) const override;
    };

    class SumEvaluationMerger : public EvaluationMerger
    {
    public:
        [[nodiscard]] int mergeEvaluations(int evaluation1, int evaluation2) const override;
    };

    class ProductEvaluationMerger : public EvaluationMerger
    {
    public:
        [[nodiscard]] int mergeEvaluations(int evaluation1, int evaluation2) const override;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EVALUATIONMERGER_H
