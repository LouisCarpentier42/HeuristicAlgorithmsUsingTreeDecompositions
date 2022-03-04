//
// Created by louis on 06/02/2022.
//

#include "ColourAssignments.h"

#include <utility>
#include "HappyVerticesAssignments.h"

DataStructures::ColourAssignments::ColourAssignments(const DataStructures::Graph* graph)
    : assignments{std::vector<DataStructures::ColourType>(graph->getNbVertices(), 0)},
      vertexKnownToBeUncoloured{std::vector<bool>(graph->getNbVertices(), false)},
      childAssignments{}
{ }

DataStructures::ColourAssignments::ColourAssignments(
        const DataStructures::Node* node,
        DataStructures::ColourAssignments* other)
    : assignments{std::vector<DataStructures::ColourType>(other->assignments.size(), 0)},
      vertexKnownToBeUncoloured{std::vector<bool>(other->assignments.size(), false)},
      childAssignments{other}
{
    for (DataStructures::VertexType vertex : node->getBagContent())
        assignments[vertex] = other->getColour(vertex);
}

DataStructures::ColourAssignments::ColourAssignments(
        const DataStructures::Node* node,
        DataStructures::ColourAssignments* primaryColourAssignment,
        DataStructures::ColourAssignments* secondaryColourAssignment)
    : assignments{std::vector<DataStructures::ColourType>(primaryColourAssignment->assignments.size(), 0)},
      vertexKnownToBeUncoloured{std::vector<bool>(primaryColourAssignment->assignments.size(), false)},
      childAssignments{primaryColourAssignment, secondaryColourAssignment}
{
    for (DataStructures::VertexType vertex : node->getBagContent())
        assignments[vertex] = primaryColourAssignment->getColour(vertex);
}

DataStructures::VertexType DataStructures::ColourAssignments::getColour(DataStructures::VertexType vertex)
{
    if (assignments[vertex] != 0)
        return assignments[vertex];

    if (vertexKnownToBeUncoloured[vertex])
        return 0;

    for (DataStructures::ColourAssignments* childAssignment : childAssignments)
    {
        DataStructures::ColourType colourInChild = childAssignment->getColour(vertex);
        if (colourInChild != 0)
        {
            assignments[vertex] = colourInChild; // Cache the colour of the vertex
            return colourInChild;
        }
    }

    vertexKnownToBeUncoloured[vertex] = true;
    return 0;
}

DataStructures::VertexType DataStructures::ColourAssignments::getColour(const DataStructures::VertexType& vertex) const
{
    if (assignments[vertex] != 0)
        return assignments[vertex];

    if (vertexKnownToBeUncoloured[vertex])
        return 0;

    for (DataStructures::ColourAssignments* childAssignment : childAssignments)
    {
        DataStructures::ColourType colourInChild = childAssignment->getColour(vertex);
        if (colourInChild != 0)
        {
            return colourInChild;
        }
    }
    return assignments[vertex];
}

bool DataStructures::ColourAssignments::isColoured(DataStructures::VertexType vertex)
{
    return getColour(vertex) != 0;
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

std::ostream& DataStructures::operator<<(std::ostream& out, DataStructures::ColourAssignments& assignments)
{
    out << "[" << assignments.getColour(0);
    for (int i{1}; i < assignments.assignments.size(); i++)
        out << ", " << assignments.getColour(i);
    return out << "]";
}

