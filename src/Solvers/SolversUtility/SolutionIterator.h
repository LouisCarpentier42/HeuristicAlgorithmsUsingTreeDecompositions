//
// Created by louis on 13/02/2022.
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
