//
// Created by louis on 17/03/2022.
//

#include <algorithm>
#include "HeuristicSolverRankingV2.h"
#include "../rng.h"

SolverV2::HeuristicSolverRankingV2::Key::Key(int id, int evaluation)
    : id{id}, evaluation{evaluation} { }

bool SolverV2::operator<(const SolverV2::HeuristicSolverRankingV2::Key& k1, const SolverV2::HeuristicSolverRankingV2::Key& k2)
{
    if (k1.evaluation != k2.evaluation)
    {
        return k1.evaluation < k2.evaluation;
    }
    else
    {
        return k1.id < k2.id;
    }
}

SolverV2::HeuristicSolverRankingV2::Value::Value(
        const SolverV2::ColourAssignmentV2& colourAssignment,
        const SolverV2::HappyVertexAssignmentV2& happyVertexAssignment)
    : colourAssignment{colourAssignment},
      happyVertexAssignment{happyVertexAssignment}
{ }

SolverV2::HeuristicSolverRankingV2::HeuristicSolverRankingV2(int capacity) : capacity{capacity} { }

void SolverV2::HeuristicSolverRankingV2::push(const SolverV2::HeuristicSolverRankingV2::Entry& entry)
{
    if (!hasReachedCapacity())
    {
        // If the capacity is not reached yet, then the new entry can be inserted without any computation
        entries.insert(entry);
    }
    else
    {
        // If the capacity has been reached, then the entry should only be added if it is at least as good
        // as the worst entry
        int worstEvaluation = entries.begin()->first.evaluation;
        if (entry.first.evaluation >= worstEvaluation)
        {
            // Insert the entry
            auto insertResult = entries.insert(entry);

            // If the entry already existed, then no other entry should be removed
            if (!insertResult.second) return;

            // Find the range of elements that have the worst evaluation
            auto worstEntriesStart = entries.begin();
            auto worstEntriesEnd = entries.begin();
            do {
                worstEntriesEnd++;
            }
            while (worstEntriesEnd != entries.end() && worstEntriesEnd->first.evaluation == worstEvaluation);

            // Remove a random entry from those that have the worst evaluation
            std::uniform_int_distribution<> dis(0, std::distance(worstEntriesStart, worstEntriesEnd) - 1);
            std::advance(worstEntriesStart, dis(RNG::rng));
            entries.erase(worstEntriesStart);
        }
    }
}

void SolverV2::HeuristicSolverRankingV2::push(
        const ColourAssignmentV2& colourAssignment,
        const HappyVertexAssignmentV2& happyVerticesAssignments,
        int evaluation)
{
    push(Entry{Key{++currentEntryId, evaluation}, Value{colourAssignment, happyVerticesAssignments}});
}

bool SolverV2::HeuristicSolverRankingV2::hasReachedCapacity() const
{
    return entries.size() == capacity;
}

int SolverV2::HeuristicSolverRankingV2::size() const
{
    return entries.size();
}

SolverV2::HeuristicSolverRankingV2::Value SolverV2::HeuristicSolverRankingV2::getBestValue() const
{
    return entries.rbegin()->second;
}

std::map<SolverV2::HeuristicSolverRankingV2::Key, SolverV2::HeuristicSolverRankingV2::Value>::iterator SolverV2::HeuristicSolverRankingV2::begin()
{
    return entries.begin();
}

std::map<SolverV2::HeuristicSolverRankingV2::Key, SolverV2::HeuristicSolverRankingV2::Value>::iterator SolverV2::HeuristicSolverRankingV2::end()
{
    return entries.end();
}

std::ostream& SolverV2::operator<<(std::ostream& out, SolverV2::HeuristicSolverRankingV2& ranking)
{
    int count{1};
    for (const auto& entry : ranking)
    {
        out << "E(" << count++ << ") \t" << entry << "\n";
    }
    return out;
}

std::ostream& SolverV2::operator<<(std::ostream& out, const SolverV2::HeuristicSolverRankingV2::Entry& entry)
{
    return out << entry.first.evaluation << "\t" << entry.second.colourAssignment << "\t" << entry.second.happyVertexAssignment;
}
