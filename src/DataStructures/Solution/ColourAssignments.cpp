//
// Created by louis on 06/02/2022.
//

#include "ColourAssignments.h"
#include "HappyVerticesAssignments.h"

DataStructures::ColourAssignments::ColourAssignments(const DataStructures::Graph *graph)
    : assignments(graph->getNbVertices()) {}

DataStructures::ColourAssignments::ColourAssignments(
        const DataStructures::ColourAssignments& primaryColourAssignment,
        const DataStructures::ColourAssignments& secondaryColourAssignment)
    : assignments{secondaryColourAssignment.assignments}
{
    for (DataStructures::VertexType vertex{0}; vertex < primaryColourAssignment.assignments.size(); vertex++)
    {
        if (primaryColourAssignment.isColoured(vertex))
            assignColour(vertex, primaryColourAssignment.getColour(vertex));
    }
}

DataStructures::VertexType DataStructures::ColourAssignments::getColour(DataStructures::VertexType vertex) const
{
    return assignments[vertex];
}

bool DataStructures::ColourAssignments::isColoured(DataStructures::VertexType vertex) const
{
    return assignments[vertex] != 0;
}

void DataStructures::ColourAssignments::assignColour(DataStructures::VertexType vertex, DataStructures::ColourType colour)
{
    assignments[vertex] = colour;
}

void DataStructures::ColourAssignments::removeColour(DataStructures::VertexType vertex)
{
    assignments[vertex] = 0;
}


bool DataStructures::operator==(const DataStructures::ColourAssignments& c1, const DataStructures::ColourAssignments& c2)
{
    return c1.assignments == c2.assignments;
}

bool DataStructures::operator<(const DataStructures::ColourAssignments& c1, const DataStructures::ColourAssignments& c2)
{
    return c1.assignments < c2.assignments;
}

std::ostream& DataStructures::operator<<(std::ostream& out, const DataStructures::ColourAssignments& assignments)
{
    out << "[" << assignments.getColour(0);
    for (int i{1}; i < assignments.assignments.size(); i++)
        out << ", " << assignments.getColour(i);
    return out << "]";
}
