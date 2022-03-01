//
// Created by louis on 17/12/2021.
//

#include "TableEntry.h"

DataStructures::TableEntry::TableEntry(
        int evaluation,
        DataStructures::ColourAssignments& colourAssignments)
    : evaluation{evaluation},
      colourAssignments{colourAssignments} {}

int DataStructures::TableEntry::getEvaluation() const
{
    return evaluation;
}

DataStructures::ColourAssignments* DataStructures::TableEntry::getColourAssignments()
{
    return &colourAssignments;
}

void DataStructures::TableEntry::colourGraph(DataStructures::Graph* graph)
{
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        graph->setColour(vertex, colourAssignments.getColour(vertex));
}

bool DataStructures::operator<(DataStructures::TableEntry& entry1, DataStructures::TableEntry& entry2)
{
    if (entry1.getEvaluation() != entry2.getEvaluation())
        return entry1.getEvaluation() < entry2.getEvaluation();
    else
        return entry1.getColourAssignments() < entry2.getColourAssignments();
}

