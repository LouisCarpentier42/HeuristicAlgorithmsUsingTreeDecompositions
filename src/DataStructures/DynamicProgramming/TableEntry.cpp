//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "TableEntry.h"

DataStructures::TableEntry::TableEntry(
        int evaluation,
        std::shared_ptr<ColourAssignment>& colourAssignments)
    : evaluation{evaluation},
      colourAssignments{colourAssignments} {}

int DataStructures::TableEntry::getEvaluation() const
{
    return evaluation;
}

std::shared_ptr<DataStructures::ColourAssignment> DataStructures::TableEntry::getColourAssignments()
{
    return colourAssignments;
}

void DataStructures::TableEntry::colourGraph(std::shared_ptr<Graph>& graph)
{
    for (VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        graph->setColour(vertex, colourAssignments->getColour(vertex));
}

bool DataStructures::operator<(const TableEntry& entry1, const TableEntry& entry2)
{
    if (entry1.evaluation != entry2.evaluation)
        return entry1.evaluation < entry2.evaluation;
    else
        return entry1.colourAssignments < entry2.colourAssignments;
}

