//
// Created by louis on 17/03/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICSOLVERRANKINGV2_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICSOLVERRANKINGV2_H

#include <set>
#include "HappyVertexAssignmentV2.h"
#include "ColourAssignmentV2.h"

namespace SolverV2
{
    class HeuristicSolverRankingV2
    {
    public:
        using Entry = std::tuple<ColourAssignmentV2, HappyVertexAssignmentV2, int>;

    private:
        struct EntryComparator
        {
            bool operator()(const Entry& entry1, const Entry& entry2) const;
        };

        const int capacity;
        std::vector<Entry> entries{};
//        std::set<Entry, EntryComparator> entries{};
        // TODO maybe a vector and then write custom binary search on eval => non const iterator for caching colour/hapiness

    public:
        explicit HeuristicSolverRankingV2(int capacity);

        void push(const Entry& entry);
        void push(
                const ColourAssignmentV2& colourAssignment,
                const HappyVertexAssignmentV2& happyVerticesAssignments,
                int evaluation);

        [[nodiscard]] bool hasReachedCapacity() const;
        [[nodiscard]] int size() const;
        [[nodiscard]] Entry getBestEntry() const;

        [[nodiscard]] std::vector<Entry>::iterator begin();
        [[nodiscard]] std::vector<Entry>::iterator end();

    private:
        void insertEntry(const Entry& entry);
    };

    std::ostream& operator<<(std::ostream& out, HeuristicSolverRankingV2& ranking);
    std::ostream& operator<<(std::ostream& out, const HeuristicSolverRankingV2::Entry& entry);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICSOLVERRANKINGV2_H
