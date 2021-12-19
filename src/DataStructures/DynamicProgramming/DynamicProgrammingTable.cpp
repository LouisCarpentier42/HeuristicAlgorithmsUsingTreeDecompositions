//
// Created by louis on 17/12/2021.
//

#include "DynamicProgrammingTable.h"

#include <algorithm>

Solvers::TableEntry::TableEntry(
        int evaluation,
        std::vector<TableEntry*> nextEntries,
        std::map<DataStructures::VertexType, DataStructures::ColourType> colourMap)
    : evaluation{evaluation}, nextEntries{std::move(nextEntries)}, colourMap{std::move(colourMap)} {}

int Solvers::TableEntry::getEvaluation() const
{
    return evaluation;
}

void Solvers::TableEntry::colourGraph(DataStructures::Graph* graph) const
{
    for (const auto& [vertex, colour] : colourMap)
    {
        if (!graph->isColoured(vertex))
        {
            graph->setColour(vertex, colour);
        }
    }

    for (TableEntry* nextEntry : nextEntries)
    {
        nextEntry->colourGraph(graph);
    }
}

const Solvers::TableEntry* Solvers::DynamicProgrammingTable::getBestEntry() const
{
    return *std::max_element(
        entries.begin(),
        entries.end(),
        [](TableEntry* entry1, TableEntry* entry2){return entry1->getEvaluation() > entry2->getEvaluation();}
    );
}
