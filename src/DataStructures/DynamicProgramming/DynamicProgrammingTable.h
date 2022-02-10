//
// Created by louis on 17/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H

#include "TableEntry.h"
#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"

#include <set>
#include <ostream>

namespace DataStructures
{
    class DynamicProgrammingTable
    {
    private:
        struct table_entry_pointer_comparator
        {
            bool operator()(const TableEntry* entry1, const TableEntry* entry2) const
            {
                return *entry1 < *entry2;
            }
        };
        size_t capacity;
        std::set<TableEntry*, table_entry_pointer_comparator> entries;

    public:
        explicit DynamicProgrammingTable(size_t capacity);

        [[nodiscard]] TableEntry* getBestEntry() const;
        [[nodiscard]] TableEntry* popBestEntry();
        [[nodiscard]] bool hasReachedCapacity() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] size_t getCapacity() const;
        [[nodiscard]] size_t getNbEntries() const;
        void setCapacity(size_t capacity);
        void clear();
        void push(TableEntry* newEntry);

        void referenceTable(DynamicProgrammingTable* other);

        std::set<TableEntry*>::const_iterator begin();
        std::set<TableEntry*>::const_iterator end();

        friend std::ostream& operator<<(std::ostream& out, const DynamicProgrammingTable& table);
    };

    std::ostream& operator<<(std::ostream& out, const DynamicProgrammingTable& table);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H
