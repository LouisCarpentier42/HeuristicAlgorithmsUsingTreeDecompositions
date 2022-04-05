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
        struct Key
        {
            const int id;
            const int evaluation;
            Key(int id, int evaluation);
        };
        struct Value
        {
            ColourAssignmentV2 colourAssignment;
            HappyVertexAssignmentV2 happyVertexAssignment;
            Value(const ColourAssignmentV2& colourAssignment, const HappyVertexAssignmentV2& happyVertexAssignment);
        };
        using Entry = std::pair<const Key, Value>;

    private:
        int currentEntryId{-1};
        const int capacity;
        std::map<Key, Value> entries{};

    public:
        explicit HeuristicSolverRankingV2(int capacity);

        void push(const Entry& entry);
        void push(
                const ColourAssignmentV2& colourAssignment,
                const HappyVertexAssignmentV2& happyVerticesAssignments,
                int evaluation);

        [[nodiscard]] bool hasReachedCapacity() const;
        [[nodiscard]] int size() const;
        [[nodiscard]] Value getBestValue() const;

        [[nodiscard]] std::map<Key, Value>::iterator begin();
        [[nodiscard]] std::map<Key, Value>::iterator end();
    };

    std::ostream& operator<<(std::ostream& out, HeuristicSolverRankingV2& ranking);
    std::ostream& operator<<(std::ostream& out, const HeuristicSolverRankingV2::Entry& entry);
    bool operator<(const HeuristicSolverRankingV2::Key& k1, const HeuristicSolverRankingV2::Key& k2);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HEURISTICSOLVERRANKINGV2_H
