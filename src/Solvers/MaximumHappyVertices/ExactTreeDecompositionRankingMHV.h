//
// Created by louis on 06/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONRANKINGMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONRANKINGMHV_H

#include "../../DataStructures/Solution/ColourAssignments.h"
#include "../../DataStructures/Solution/HappyVerticesAssignments.h"

#include <limits>
#include <map>

namespace Solvers
{
    class ExactTreeDecompositionRankingMHV
    {
    public:
        static const int NEGATIVE_INFINITY = std::numeric_limits<int>::min();
        using ExactTreeDecompositionRankingKey = std::pair<const DataStructures::ColourAssignments, const DataStructures::HappyVerticesAssignments>;
        using ExactTreeDecompositionRankingValue = std::pair<int, const DataStructures::ColourAssignments*>;
        using ExactTreeDecompositionRankingIterator = const std::_Rb_tree_const_iterator<std::pair<const ExactTreeDecompositionRankingKey, ExactTreeDecompositionRankingValue>>;
        using ExactTreeDecompositionRankingEntry = std::pair<ExactTreeDecompositionRankingKey, ExactTreeDecompositionRankingValue>;

    private:
        std::map<ExactTreeDecompositionRankingKey, ExactTreeDecompositionRankingValue> solutions;

    public:
        void addSolution(
            int evaluation,
            const DataStructures::ColourAssignments& colourAssignments,
            const DataStructures::HappyVerticesAssignments& happyVerticesAssignments,
            const std::vector<const DataStructures::ColourAssignments*>& previousFullColourings
        );

        [[nodiscard]] ExactTreeDecompositionRankingEntry getBestEntry() const;
        [[nodiscard]] int getBestEvaluation() const;
        [[nodiscard]] const DataStructures::ColourAssignments* getBestFullColouring() const;

        [[nodiscard]] int getEvaluation(
            const DataStructures::ColourAssignments& colourAssignments,
            const DataStructures::HappyVerticesAssignments& happyVerticesAssignments
        ) const;
        [[nodiscard]] const DataStructures::ColourAssignments* getFullColouring(
            const DataStructures::ColourAssignments& colourAssignments,
            const DataStructures::HappyVerticesAssignments& happyVerticesAssignments
        ) const;

        [[nodiscard]] ExactTreeDecompositionRankingIterator begin() const;
        [[nodiscard]] ExactTreeDecompositionRankingIterator end() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONRANKINGMHV_H
