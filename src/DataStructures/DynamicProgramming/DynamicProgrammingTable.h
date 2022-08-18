//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H

#include "TableEntry.h"
#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"

#include <set>
#include <ostream>
#include <memory>

namespace DataStructures
{
    class DynamicProgrammingTable
    {
    private:
        struct table_entry_pointer_comparator
        {
            bool operator()(const std::shared_ptr<TableEntry>& entry1, const std::shared_ptr<TableEntry>& entry2) const
            {
                return *entry1 < *entry2;
            }
        };
        size_t capacity;
        std::set<std::shared_ptr<TableEntry>, table_entry_pointer_comparator> entries;

    public:
        explicit DynamicProgrammingTable(size_t capacity);

        [[nodiscard]] std::shared_ptr<TableEntry> getBestEntry() const;
        [[nodiscard]] std::shared_ptr<TableEntry> popBestEntry();
        [[nodiscard]] bool hasReachedCapacity() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] size_t getCapacity() const;
        [[nodiscard]] size_t getNbEntries() const;
        void setCapacity(size_t capacity);
        void clear();

        void push(std::shared_ptr<TableEntry> newEntry);
        void pop(std::shared_ptr<TableEntry>& entry);

        void referenceTable(const DynamicProgrammingTable& other);

        std::set<std::shared_ptr<TableEntry>>::const_iterator begin();
        std::set<std::shared_ptr<TableEntry>>::const_iterator end();

        friend std::ostream& operator<<(std::ostream& out, const DynamicProgrammingTable& table);
    };

    std::ostream& operator<<(std::ostream& out, const DynamicProgrammingTable& table);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H
