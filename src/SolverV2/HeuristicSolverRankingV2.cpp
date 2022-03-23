//
// Created by louis on 17/03/2022.
//

#include <algorithm>
#include "HeuristicSolverRankingV2.h"
#include "../rng.h"


SolverV2::HeuristicSolverRankingV2::HeuristicSolverRankingV2(int capacity) : capacity{capacity} { }

void SolverV2::HeuristicSolverRankingV2::push(
        const ColourAssignmentV2& colourAssignment,
        const HappyVertexAssignmentV2& happyVerticesAssignments,
        int evaluation)
{
//    for (const Entry& entry : entries)
//    {
//        if (std::get<0>(entry) == colourAssignment && std::get<1>(entry) == happyVerticesAssignments)
//        {
//            if (evaluation > std::get<2>(entry))
//            {
////                entries.erase(entry);
//                entries.erase(std::remove(entries.begin(), entries.end(), entry), entries.end()); // TODO
////                entries.insert(std::make_tuple(colourAssignment, happyVerticesAssignments, evaluation));
//                entries.emplace_back(colourAssignment, happyVerticesAssignments, evaluation);
//
//                if (std::get<2>(entry) == worstEvaluation)
//                {
//                    worstEntries.erase(entry);
//                    if (worstEntries.empty())
//                    {
//                        worstEvaluation = std::get<2>(*entries.begin());
//                        for (const Entry& existingEntry : entries)
//                        {
//                            if (std::get<2>(existingEntry) < worstEvaluation)
//                            {
//                                worstEvaluation = std::get<2>(existingEntry);
//                                worstEntries.clear();
//                                worstEntries.insert(existingEntry);
//                            }
//                            else if (std::get<2>(existingEntry) == worstEvaluation)
//                            {
//                                worstEntries.insert(existingEntry);
//                            }
//                        }
//                    }
//                }
//            }
//
//            return;
//        }
//    }


    if (entries.empty())
    {
        Entry entry = std::make_tuple(colourAssignment, happyVerticesAssignments, evaluation);
//        entries.insert(entry);
        entries.push_back(entry);
        worstEntries.insert(entry);
        worstEvaluation = evaluation;
    }
    else if (!hasReachedCapacity())
    {
        Entry entry = std::make_tuple(colourAssignment, happyVerticesAssignments, evaluation);
//        entries.insert(entry);
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
//        entries.insert(entry);
        entries.push_back(entry);
        if (worstEvaluation == evaluation)
            worstEntries.insert(entry);

        if (worstEntries.size() == 1)
        {
//            entries.erase(*worstEntries.begin());
            entries.erase(std::remove(entries.begin(), entries.end(), *worstEntries.begin()), entries.end()); // TODO
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
//            entries.erase(*randomWorstEntryIt);
            entries.erase(std::remove(entries.begin(), entries.end(), *randomWorstEntryIt), entries.end()); // TODO
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
    return *std::max_element(
            entries.begin(),
            entries.end(),
            [](const Entry& entry1, const Entry& entry2){ return std::get<2>(entry1) < std::get<2>(entry2); }
        );
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
        out << "E(" << count++ << ") \t" << entry << "\n";
    }
    return out;
}

std::ostream& SolverV2::operator<<(std::ostream& out, const SolverV2::HeuristicSolverRankingV2::Entry& entry)
{
    return out << std::get<2>(entry) << "\t" << std::get<0>(entry) << "\t" << std::get<1>(entry);
}
