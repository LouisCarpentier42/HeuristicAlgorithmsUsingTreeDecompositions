//
// Created by louis on 06/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONRANKINGMHV_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONRANKINGMHV_H

#include "../../../DataStructures/Solution/ColourAssignment.h"
#include "../../../DataStructures/Solution/HappyVerticesAssignments.h"

#include <limits>
#include <map>

namespace Solvers
{
    class ExactTreeDecompositionRankingMHV
    {
    public:
        static const int NEGATIVE_INFINITY = std::numeric_limits<int>::min();
        using ExactTreeDecompositionRankingKey = std::pair<const DataStructures::ColourAssignment, const DataStructures::HappyVerticesAssignments>;
        using ExactTreeDecompositionRankingValue = std::pair<int, const std::shared_ptr<DataStructures::ColourAssignment>>;
        using ExactTreeDecompositionRankingIterator = const std::_Rb_tree_const_iterator<std::pair<const ExactTreeDecompositionRankingKey, ExactTreeDecompositionRankingValue>>;
        using ExactTreeDecompositionRankingEntry = std::pair<ExactTreeDecompositionRankingKey, ExactTreeDecompositionRankingValue>;

    private:
        std::map<ExactTreeDecompositionRankingKey, ExactTreeDecompositionRankingValue> solutions;

    public:
        void addSolution(
            int evaluation,
            const DataStructures::ColourAssignment& colourAssignments,
            const DataStructures::HappyVerticesAssignments& happyVerticesAssignments,
            const std::vector<std::shared_ptr<DataStructures::ColourAssignment>>& previousFullColourings
        );

        [[nodiscard]] ExactTreeDecompositionRankingEntry getBestEntry() const;
        [[nodiscard]] int getBestEvaluation() const;
        [[nodiscard]] std::shared_ptr<DataStructures::ColourAssignment> getBestFullColouring() const;

        [[nodiscard]] int getEvaluation(
            const DataStructures::ColourAssignment& colourAssignments,
            const DataStructures::HappyVerticesAssignments& happyVerticesAssignments
        ) const;
        [[nodiscard]] std::shared_ptr<DataStructures::ColourAssignment> getFullColouring(
            const DataStructures::ColourAssignment& colourAssignments,
            const DataStructures::HappyVerticesAssignments& happyVerticesAssignments
        ) const;

        [[nodiscard]] ExactTreeDecompositionRankingIterator begin() const;
        [[nodiscard]] ExactTreeDecompositionRankingIterator end() const;
    };

    std::ostream& operator<<(std::ostream& out, ExactTreeDecompositionRankingMHV& ranking);
    std::ostream& operator<<(std::ostream& out, const ExactTreeDecompositionRankingMHV::ExactTreeDecompositionRankingEntry& entry);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONRANKINGMHV_H
