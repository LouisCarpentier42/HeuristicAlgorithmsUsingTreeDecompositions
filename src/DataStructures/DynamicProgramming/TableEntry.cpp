//
// Created by louis on 17/12/2021.
//

#include "TableEntry.h"

DataStructures::TableEntry::TableEntry(
        int evaluation,
        const DataStructures::ColourAssignments& colourAssignments)
    : evaluation{evaluation},
      colourAssignments{colourAssignments} {}

int DataStructures::TableEntry::getEvaluation() const
{
    return evaluation;
}

DataStructures::ColourAssignments DataStructures::TableEntry::getColourAssignments() const
{
    return colourAssignments;
}

void DataStructures::TableEntry::colourGraph(DataStructures::Graph* graph) const
{
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        graph->setColour(vertex, colourAssignments.getColour(vertex));
}

bool DataStructures::operator<(const DataStructures::TableEntry& entry1, const DataStructures::TableEntry& entry2)
{
    if (entry1.getEvaluation() != entry2.getEvaluation())
        return entry1.getEvaluation() < entry2.getEvaluation();
    else
        return entry1.getColourAssignments() < entry2.getColourAssignments();
}

