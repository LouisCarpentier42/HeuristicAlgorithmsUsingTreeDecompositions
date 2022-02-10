//
// Created by louis on 17/12/2021.
//

#include "DynamicProgrammingTable.h"

#include <algorithm>
#include <random>

DataStructures::DynamicProgrammingTable::DynamicProgrammingTable(size_t capacity)
    : capacity{capacity} {}

DataStructures::TableEntry* DataStructures::DynamicProgrammingTable::getBestEntry() const
{
    return *std::prev(entries.end());
}

DataStructures::TableEntry* DataStructures::DynamicProgrammingTable::popBestEntry()
{
    DataStructures::TableEntry* bestEntry = *std::prev(entries.end());
    entries.erase(std::prev(entries.end()));
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

size_t DataStructures::DynamicProgrammingTable::getNbEntries() const
{
    return entries.size();
}

void DataStructures::DynamicProgrammingTable::setCapacity(size_t capacity)
{
    this->capacity = capacity;
    clear();
}

void DataStructures::DynamicProgrammingTable::clear()
{
    entries.clear();
}

void DataStructures::DynamicProgrammingTable::push(DataStructures::TableEntry* newEntry)
{
    // Check if there is already an entry with identical colour assignment
    auto iterator = entries.begin();
    while (iterator != entries.end())
    {
        if (newEntry->getColourAssignments() == (*iterator)->getColourAssignments())
        {
            // If there exists another entry with the same colour assignment, then it will be replaced
            // only if the evaluation of the new entry is greater than that of the existing entry.
            if ((*iterator)->getEvaluation() < newEntry->getEvaluation())
            {
                entries.erase(iterator);
                entries.insert(newEntry);
            }
            return;
        }
        iterator++;
    }

    entries.insert(newEntry);
    if (entries.size() > capacity)
    {
        // Find the range of elements that have the worst evaluation and select a random element from it to erase
        auto worstEntriesStart = entries.begin();
        auto worstEntriesEnd = entries.begin();
        do {
            worstEntriesEnd++;
        }
        while (worstEntriesEnd != entries.end() &&
            (*worstEntriesEnd)->getEvaluation() == (*entries.begin())->getEvaluation());

        static std::mt19937 rng{std::random_device{}()};
        std::uniform_int_distribution<> dis(0, std::distance(worstEntriesStart, worstEntriesEnd) - 1);
        std::advance(worstEntriesStart, dis(rng));
        entries.erase(worstEntriesStart);
    }
}

void DataStructures::DynamicProgrammingTable::referenceTable(DataStructures::DynamicProgrammingTable* other)
{
    for (TableEntry* entry : other->entries)
        push(entry);
}

std::set<DataStructures::TableEntry *>::const_iterator DataStructures::DynamicProgrammingTable::begin()
{
    return entries.begin();
}

std::set<DataStructures::TableEntry *>::const_iterator DataStructures::DynamicProgrammingTable::end()
{
    return entries.end();
}

std::ostream& DataStructures::operator<<(std::ostream& out, const DataStructures::DynamicProgrammingTable& table)
{
    int count{1};
    for (DataStructures::TableEntry* entry : table.entries)
        out << "E(" << count++ << "): " << entry->getEvaluation() << " " << entry->getColourAssignments() << "\n";
    return out;
}



