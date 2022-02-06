//
// Created by louis on 06/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONRANKING_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONRANKING_H

#include "../../../DataStructures/Solution/ColourAssignments.h"
#include "../../../DataStructures/Solution/HappyVerticesAssignments.h"

#include <limits>
#include <map>



namespace MaximumHappyVertices
{
    class ExactTreeDecompositionRanking
    {
    public:
        static int NEGATIVE_INFINITY = std::numeric_limits<int>::min();
        using ExactTreeDecompositionSolution = std::pair<const DataStructures::ColourAssignments, const DataStructures::HappyVerticesAssignments>;
        using ExactTreeDecompositionRankingIterator = const std::_Rb_tree_const_iterator<std::pair<const ExactTreeDecompositionSolution , int>>;

    private:
        std::map<ExactTreeDecompositionSolution, int> solutions{};

    public:
        void addSolution(
            int evaluation,
            const DataStructures::ColourAssignments& colourAssignments,
            const DataStructures::HappyVerticesAssignments& happyVerticesAssignments
        );

        [[nodiscard]] int getEvaluation(
            const DataStructures::ColourAssignments& colourAssignments,
            const DataStructures::HappyVerticesAssignments& happyVerticesAssignments
        ) const;

        [[nodiscard]] ExactTreeDecompositionRankingIterator begin() const;
        [[nodiscard]] ExactTreeDecompositionRankingIterator end() const;
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONRANKING_H
