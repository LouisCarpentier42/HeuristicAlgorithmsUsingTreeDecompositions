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

        struct Entry
        {
            int id{0};
            ColourAssignmentV2 colourAssignment;
            HappyVertexAssignmentV2 happyVertexAssignment;
            int evaluation;

            Entry(int id, const ColourAssignmentV2& colourAssignment, const HappyVertexAssignmentV2& happyVertexAssignment, int evaluation);
        };

    private:
        struct EntryComparator
        {
            bool operator()(const Entry& entry1, const Entry& entry2) const;
        };

        int currentEntryId{-1};
        const int capacity;
        std::set<Entry, EntryComparator> entries{};

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

        [[nodiscard]] std::set<Entry>::iterator begin();
        [[nodiscard]] std::set<Entry>::iterator end();
    };

    std::ostream& operator<<(std::ostream& out, HeuristicSolverRankingV2& ranking);
    std::ostream& operator<<(std::ostream& out, const HeuristicSolverRankingV2::Entry& entry);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICSOLVERRANKINGV2_H
