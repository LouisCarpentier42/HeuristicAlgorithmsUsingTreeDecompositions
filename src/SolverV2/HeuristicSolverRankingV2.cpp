//
// Created by louis on 17/03/2022.
//

#include <algorithm>
#include "HeuristicSolverRankingV2.h"
#include "../rng.h"


SolverV2::HeuristicSolverRankingV2::HeuristicSolverRankingV2(int capacity) : capacity{capacity} { }

void SolverV2::HeuristicSolverRankingV2::push(
        const std::shared_ptr<DataStructures::ColourAssignment>& colourAssignment,
        const DataStructures::HappyVerticesAssignments& happyVerticesAssignments,
        int evaluation)
{
//    for (Entry& entry : entries)
//    {
//        if (std::get<0>(entry) == colourAssignment && std::get<1>(entry) == happyVerticesAssignments)
//        {
//            if (evaluation > std::get<2>(entry))
//                std::get<2>(entry) = evaluation;
//            return; // TODO also check worst entries
//        }
//    }

    if (entries.empty())
    {
        Entry entry = std::make_tuple(colourAssignment, happyVerticesAssignments, evaluation);
        entries.push_back(entry);
        worstEntries.insert(entry);
        worstEvaluation = evaluation;
    }
    else if (!hasReachedCapacity())
    {
        Entry entry = std::make_tuple(colourAssignment, happyVerticesAssignments, evaluation);
        entries.push_back(entry);
        if (worstEvaluation == evaluation)
        {
            worstEntries.insert(entry);
        }
        else if (worstEvaluation > evaluation)
        {
            worstEvaluation = evaluation;
            worstEntries.clear();
            worstEntries.insert(entry);
        }
    }
    else
    {
        if (worstEvaluation > evaluation) return;

        Entry entry = std::make_tuple(colourAssignment, happyVerticesAssignments, evaluation);
        entries.push_back(entry);
        if (worstEvaluation == evaluation)
            worstEntries.insert(entry);

        if (worstEntries.size() == 1)
        {
            entries.erase(std::remove(entries.begin(), entries.end(), *worstEntries.begin()), entries.end());
            worstEntries.clear();

            // Reset the worst entries
            worstEvaluation = std::get<2>(*entries.begin());
            for (const Entry& existingEntry : entries)
            {
                if (std::get<2>(existingEntry) < worstEvaluation)
                {
                    worstEvaluation = std::get<2>(existingEntry);
                    worstEntries.clear();
                    worstEntries.insert(existingEntry);
                }
                else if (std::get<2>(existingEntry) == worstEvaluation)
                {
                    worstEntries.insert(existingEntry);
                }
            }
        }
        else
        {
            auto randomWorstEntryIt = worstEntries.begin();
            std::uniform_int_distribution<> dis(0, std::distance(worstEntries.begin(), worstEntries.end()) - 1);
            std::advance(randomWorstEntryIt, dis(RNG::rng));
            entries.erase(std::remove(entries.begin(), entries.end(), *randomWorstEntryIt), entries.end());
            worstEntries.erase(randomWorstEntryIt);
        }
    }
}

bool SolverV2::HeuristicSolverRankingV2::hasReachedCapacity() const
{
    return entries.size() == capacity;
}

std::vector<SolverV2::HeuristicSolverRankingV2::Entry>::iterator SolverV2::HeuristicSolverRankingV2::begin()
{
    return entries.begin();
}

std::vector<SolverV2::HeuristicSolverRankingV2::Entry>::iterator SolverV2::HeuristicSolverRankingV2::end()
{
    return entries.end();
}

SolverV2::HeuristicSolverRankingV2::Entry SolverV2::HeuristicSolverRankingV2::getBestEntry() const
{
    // TODO with max element
    Entry bestEntry = *entries.begin();
    for (Entry entry : entries)
    {
        if (std::get<2>(entry) > std::get<2>(bestEntry))
            bestEntry = entry;
    }
    return bestEntry;
}

int SolverV2::HeuristicSolverRankingV2::size() const
{
    return entries.size();
}

std::ostream& SolverV2::operator<<(std::ostream& out, SolverV2::HeuristicSolverRankingV2& ranking)
{
    int count{1};
    for (const SolverV2::HeuristicSolverRankingV2::Entry& entry : ranking)
    {
        out << "E(" << count++ << ") \t" << entry;
    }
    return out;
}

std::ostream& SolverV2::operator<<(std::ostream& out, const SolverV2::HeuristicSolverRankingV2::Entry& entry)
{
    out << std::get<2>(entry) << "\t" << *std::get<0>(entry);

    out << "\t[";
    if (std::get<0>(entry)->isColoured(0))
        out << (std::get<1>(entry).isHappy(0) ? "H" : "U");
    else
        out << ".";
    for (DataStructures::VertexType vertex{1}; vertex < std::get<0>(entry)->getSize(); vertex++)
    {
        if (std::get<0>(entry)->isColoured(vertex))
            out << ", " << (std::get<1>(entry).isHappy(vertex) ? "H" : "U");
        else
            out << ", " << ".";
    }

    out << "]\n";
    return out;
}




