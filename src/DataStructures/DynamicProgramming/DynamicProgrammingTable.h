//
// Created by louis on 17/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H

#include "TableEntry.h"
#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"

#include <vector>
#include <ostream>

// TODO optimize (eg with std::set)

namespace DataStructures
{
    class DynamicProgrammingTable
    {
    private:
        size_t capacity;
        std::vector<TableEntry*> entries;

    public:
        explicit DynamicProgrammingTable(size_t capacity);

        [[nodiscard]] TableEntry* getBestEntry() const;
        [[nodiscard]] TableEntry* popBestEntry();
        [[nodiscard]] bool hasReachedCapacity() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] size_t getCapacity() const;
        void setCapacity(size_t capacity);
        void clear();
        void push(TableEntry* entry);

        void referenceTable(DynamicProgrammingTable* other);

        std::vector<TableEntry*>::const_iterator begin();
        std::vector<TableEntry*>::const_iterator end();

        friend std::ostream& operator<<(std::ostream& out, const DynamicProgrammingTable& table);
    };

    std::ostream& operator<<(std::ostream& out, const DynamicProgrammingTable& table);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H
