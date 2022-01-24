//
// Created by louis on 17/12/2021.
//

#include "DynamicProgrammingTable.h"

#include <algorithm>

DataStructures::DynamicProgrammingTable::DynamicProgrammingTable(size_t capacity)
    : capacity{capacity} {}

DataStructures::TableEntry* DataStructures::DynamicProgrammingTable::getBestEntry() const
{
    return *std::max_element(
        entries.begin(),
        entries.end(),
        [](TableEntry* entry1, TableEntry* entry2){return entry1->getEvaluation() < entry2->getEvaluation();}
    );
}

DataStructures::TableEntry* DataStructures::DynamicProgrammingTable::popBestEntry()
{
    std::sort(
        entries.begin(),
        entries.end(),
        [](TableEntry* entry1, TableEntry* entry2){return entry1->getEvaluation() < entry2->getEvaluation();}
    );
    DataStructures::TableEntry* bestEntry = entries.back();
    entries.pop_back();
    return bestEntry;
}

bool DataStructures::DynamicProgrammingTable::empty() const
{
    return entries.empty();
}

bool DataStructures::DynamicProgrammingTable::hasReachedCapacity() const
{
    return entries.size() >= capacity;
}

size_t DataStructures::DynamicProgrammingTable::getCapacity() const
{
    return capacity;
}

void DataStructures::DynamicProgrammingTable::setCapacity(size_t capacity)
{
    this->capacity = capacity;
    entries.resize(capacity);
    clear();
}

void DataStructures::DynamicProgrammingTable::clear()
{
    entries.clear();
}

void DataStructures::DynamicProgrammingTable::push(DataStructures::TableEntry* entry)
{
    // There can't be two entries with identical colour assignment
    for (int i{0}; i < entries.size(); i++)
    {
        if (entry->getColourAssignments() == entries[i]->getColourAssignments())
        {
            if (entry->getEvaluation() > entries[i]->getEvaluation()) // TODO maybe check if ever a different eval
            {
                delete entries[i]; // TODO not sure if needed?
                entries[i] = entry;
            }
            return;
        }
    }

    entries.push_back(entry);

    if (entries.size() > capacity)
    {
        auto worstEntryIt = std::min_element(
            entries.begin(),
            entries.end(),
            [](TableEntry* entry1, TableEntry* entry2){return entry1->getEvaluation() < entry2->getEvaluation();}
        );
        entries.erase(worstEntryIt);
    }

//    // TODO OLD VERSION IN COLOURINGQUEUE
//
//    // Prune the queue if it has too many elements
//    if (queue.size() > nbColourings)
//    {
//        // Find the worst element in the queue
//        auto it = std::min_element(queue.begin(), queue.end(),
//                                   [this](auto* c1, auto* c2){return evaluator->compare(graph, c1, c2);});
//
//        // Remove all the elements in the queue that have the worst evaluation
//        int worstEvaluation{evaluator->evaluate(graph, *it)};
//        std::vector<DataStructures::MutableColouring*>allColourings{queue};
//        queue.clear();
//        std::copy_if(
//                allColourings.begin(),
//                allColourings.end(),
//                std::back_inserter(queue),
//                [this,worstEvaluation](auto* c){return evaluator->evaluate(graph, c)>worstEvaluation;}
//                );
//
//        // If the queue is not full, then add random colourings with the worst evaluation to fill it
//        if (queue.size() < nbColourings)
//        {
//            std::vector<DataStructures::MutableColouring*>fillUpColourings{};
//            std::copy_if(
//                    allColourings.begin(),
//                    allColourings.end(),
//                    std::back_inserter(fillUpColourings),
//                    [this,worstEvaluation](auto* c){return evaluator->evaluate(graph, c)==worstEvaluation;}
//                    );
//            std::sample(
//                    fillUpColourings.begin(),
//                    fillUpColourings.end(),
//                    std::back_inserter(queue),
//                    nbColourings - queue.size(),
//                    std::mt19937{std::random_device{}()}
//                    );
//        }
//
//        if (queue.empty())
//        {
//            queue = allColourings;
//
//            //            // If all colouring have the same (worst) evaluation, then sample some randomly
//            //            std::sample(
//            //                allColourings.begin(),
//            //                allColourings.end(),
//            //                std::back_inserter(queue),
//            //                nbColourings,
//            //                std::mt19937{std::random_device{}()}
//            //            );
//        }
//    }
}

void DataStructures::DynamicProgrammingTable::referenceTable(DataStructures::DynamicProgrammingTable* other)
{
    for (TableEntry* entry : other->entries)
        push(entry);
}

std::vector<DataStructures::TableEntry *>::const_iterator DataStructures::DynamicProgrammingTable::begin()
{
    return entries.begin();
}

std::vector<DataStructures::TableEntry *>::const_iterator DataStructures::DynamicProgrammingTable::end()
{
    return entries.end();
}

std::ostream& DataStructures::operator<<(std::ostream& out, const DataStructures::DynamicProgrammingTable& table)
{
    int count{1};
    for (DataStructures::TableEntry* entry : table.entries)
    {
        out << "E(" << count++ << "): " << entry->getEvaluation() << " " << entry->getColourAssignments() << "\n";
    }
    return out;
}



