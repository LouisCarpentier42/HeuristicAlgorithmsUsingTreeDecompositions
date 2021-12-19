//
// Created by louis on 17/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H

#include "../../DataStructures/DataStructuresAliases.h"
#include "../../DataStructures/Graph/Graph.h"

#include <map>
#include <vector>

namespace Solvers
{

    class TableEntry
    {
    private:
        const int evaluation;
        std::vector<TableEntry*> nextEntries;
        std::map<DataStructures::VertexType, DataStructures::ColourType> colourMap;

    public:
        TableEntry(
            int evaluation,
            std::vector<TableEntry*> nextEntries,
            std::map<DataStructures::VertexType, DataStructures::ColourType> colourMap
        );
        [[nodiscard]] int getEvaluation() const;
        void colourGraph(DataStructures::Graph* graph) const;
    };


    class DynamicProgrammingTable
    {
        std::vector<TableEntry*> entries;

        [[nodiscard]] const TableEntry* getBestEntry() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DYNAMICPROGRAMMINGTABLE_H
