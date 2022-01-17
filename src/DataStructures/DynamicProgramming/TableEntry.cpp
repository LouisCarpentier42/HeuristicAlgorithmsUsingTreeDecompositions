//
// Created by louis on 17/12/2021.
//

#include "TableEntry.h"

DataStructures::TableEntry::TableEntry(
        int evaluation,
        DataStructures::TableEntry::NextEntries nextEntries,
        DataStructures::TableEntry::ColourAssignments& colourAssignments)
    : evaluation{evaluation},
      nextEntries{std::move(nextEntries)},
      colourAssignments{colourAssignments} {}

int DataStructures::TableEntry::getEvaluation() const
{
    return evaluation;
}

DataStructures::TableEntry::ColourAssignments DataStructures::TableEntry::getColourAssignments() const
{
    return colourAssignments;
}

void DataStructures::TableEntry::colourGraph(DataStructures::Graph* graph) const
{
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        graph->setColour(vertex, colourAssignments.getColour(vertex));
}

DataStructures::TableEntry::ColourAssignments::ColourAssignments(const DataStructures::Graph *graph)
    : assignments(graph->getNbVertices()) {}

DataStructures::TableEntry::ColourAssignments::ColourAssignments(
        const DataStructures::TableEntry::ColourAssignments& primaryColourAssignment,
        const DataStructures::TableEntry::ColourAssignments& secondaryColourAssignment)
    : assignments{secondaryColourAssignment.assignments}
{
    for (DataStructures::VertexType vertex{0}; vertex < primaryColourAssignment.assignments.size(); vertex++)
    {
        if (primaryColourAssignment.isColoured(vertex))
            assignColour(vertex, primaryColourAssignment.getColour(vertex));
    }
}

DataStructures::VertexType DataStructures::TableEntry::ColourAssignments::getColour(DataStructures::VertexType vertex) const
{
    return assignments[vertex];
}

bool DataStructures::TableEntry::ColourAssignments::isColoured(DataStructures::VertexType vertex) const
{
    return assignments[vertex] != 0;
}

void DataStructures::TableEntry::ColourAssignments::assignColour(DataStructures::VertexType vertex, DataStructures::ColourType colour)
{
    assignments[vertex] = colour;
}

