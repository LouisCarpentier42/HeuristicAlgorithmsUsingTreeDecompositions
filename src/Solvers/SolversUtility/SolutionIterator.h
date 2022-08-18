//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLUTIONITERATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLUTIONITERATOR_H

namespace Solvers
{
    template <typename T>
    class SolutionIterator
    {
        [[nodiscard]] virtual const T getValue() const = 0;
        [[nodiscard]] virtual bool next() = 0;
    };
}


#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLUTIONITERATOR_H
