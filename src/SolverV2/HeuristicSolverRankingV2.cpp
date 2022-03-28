//
// Created by louis on 17/03/2022.
//

#include <algorithm>
#include "HeuristicSolverRankingV2.h"
#include "../rng.h"


bool SolverV2::HeuristicSolverRankingV2::EntryComparator::operator()(
        const SolverV2::HeuristicSolverRankingV2::Entry &entry1,
        const SolverV2::HeuristicSolverRankingV2::Entry &entry2) const
{
    if (std::get<2>(entry1) != std::get<2>(entry2))
    {
        return std::get<2>(entry1) < std::get<2>(entry2);
    }
    else
    {
        return entry1 < entry2;
    }
}

SolverV2::HeuristicSolverRankingV2::HeuristicSolverRankingV2(int capacity) : capacity{capacity} { }

void SolverV2::HeuristicSolverRankingV2::push(const SolverV2::HeuristicSolverRankingV2::Entry& entry)
{
    if (!hasReachedCapacity())
    {
        // If the capacity is not reached yet, then the new entry can be inserted without any computation
//        insertEntry(entry);
        entries.insert(entry);
    }
    else
    {
        // If the capacity has been reached, then the entry should only be added if it is at least as good
        // as the worst entry
        int worstEvaluation = std::get<2>(*entries.begin());
        if (std::get<2>(entry) >= worstEvaluation)
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
            while (worstEntriesEnd != entries.end() && std::get<2>(*worstEntriesEnd) == worstEvaluation);

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
    push(std::make_tuple(colourAssignment, happyVerticesAssignments, evaluation));
}

bool SolverV2::HeuristicSolverRankingV2::hasReachedCapacity() const
{
    return entries.size() == capacity;
}

int SolverV2::HeuristicSolverRankingV2::size() const
{
    return entries.size();
}

SolverV2::HeuristicSolverRankingV2::Entry SolverV2::HeuristicSolverRankingV2::getBestEntry() const
{
    return *entries.rbegin();
}

std::set<SolverV2::HeuristicSolverRankingV2::Entry>::iterator SolverV2::HeuristicSolverRankingV2::begin()
{
    return entries.begin();
}

std::set<SolverV2::HeuristicSolverRankingV2::Entry>::iterator SolverV2::HeuristicSolverRankingV2::end()
{
    return entries.end();
}

std::ostream& SolverV2::operator<<(std::ostream& out, SolverV2::HeuristicSolverRankingV2& ranking)
{
    int count{1};
    for (const SolverV2::HeuristicSolverRankingV2::Entry& entry : ranking)
    {
        out << "E(" << count++ << ") \t" << entry << "\n";
    }
    return out;
}

std::ostream& SolverV2::operator<<(std::ostream& out, const SolverV2::HeuristicSolverRankingV2::Entry& entry)
{
    return out << std::get<2>(entry) << "\t" << std::get<0>(entry) << "\t" << std::get<1>(entry);
}
