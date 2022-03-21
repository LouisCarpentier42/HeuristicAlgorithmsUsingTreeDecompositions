//
// Created by louis on 06/02/2022.
//

#include "ColourAssignment.h"


DataStructures::ColourAssignment::ColourAssignment(size_t size)
    : assignments{std::vector<ColourType>(size, 0)},
     vertexKnownToBeUncoloured{std::vector<bool>(size, false)},
     childAssignments{}
{ }

DataStructures::ColourAssignment::ColourAssignment(const std::shared_ptr<Graph>& graph)
    : ColourAssignment(graph->getNbVertices())
{ }

DataStructures::ColourAssignment::ColourAssignment(
        const std::shared_ptr<Node>& node,
        std::shared_ptr<ColourAssignment>& other)
    : assignments{std::vector<ColourType>(other->assignments.size(), 0)},
      vertexKnownToBeUncoloured{std::vector<bool>(other->assignments.size(), false)},
      childAssignments{other}
{
    for (VertexType vertex : node->getBagContent())
        assignments[vertex] = other->getColour(vertex);
}

DataStructures::ColourAssignment::ColourAssignment(
        const std::shared_ptr<Node>& node,
        const std::shared_ptr<ColourAssignment>& primaryColourAssignment,
        const std::shared_ptr<ColourAssignment>& secondaryColourAssignment)
    : assignments{std::vector<ColourType>(primaryColourAssignment->assignments.size(), 0)},
      vertexKnownToBeUncoloured{std::vector<bool>(primaryColourAssignment->assignments.size(), false)},
      childAssignments{primaryColourAssignment, secondaryColourAssignment}
{
    for (VertexType vertex : node->getBagContent())
        assignments[vertex] = primaryColourAssignment->getColour(vertex);
}

size_t DataStructures::ColourAssignment::getSize() const
{
    return assignments.size();
}

DataStructures::ColourType DataStructures::ColourAssignment::getColour(VertexType vertex)
{
    if (assignments[vertex] != 0)
        return assignments[vertex];

    if (vertexKnownToBeUncoloured[vertex])
        return 0;

    for (std::shared_ptr<ColourAssignment>& childAssignment : childAssignments)
    {
        ColourType colourInChild = childAssignment->getColour(vertex);
        if (colourInChild != 0)
        {
            assignments[vertex] = colourInChild; // Cache the colour of the vertex
            return colourInChild;
        }
    }

    vertexKnownToBeUncoloured[vertex] = true;
    return 0;
}

DataStructures::ColourType DataStructures::ColourAssignment::getColourConst(const VertexType& vertex) const // TODO rename back to non const
{
    if (assignments[vertex] != 0)
        return assignments[vertex];

    if (vertexKnownToBeUncoloured[vertex])
        return 0;

    for (const std::shared_ptr<ColourAssignment>& childAssignment : childAssignments)
    {
        ColourType colourInChild = childAssignment->getColour(vertex);
        if (colourInChild != 0)
        {
            return colourInChild;
        }
    }
    return assignments[vertex];
}

bool DataStructures::ColourAssignment::isColoured(VertexType vertex)
{
    return getColour(vertex) != 0;
}

bool DataStructures::ColourAssignment::isColouredConst(VertexType vertex) const // TODO rename back to non const
{
    return getColourConst(vertex) != 0;
}

void DataStructures::ColourAssignment::assignColour(VertexType vertex, ColourType colour)
{
    assignments[vertex] = colour;
}

void DataStructures::ColourAssignment::removeColour(VertexType vertex)
{
    assignments[vertex] = 0;
}

bool DataStructures::operator==(const DataStructures::ColourAssignment& c1, const DataStructures::ColourAssignment& c2)
{
    return c1.assignments == c2.assignments;
}

bool DataStructures::operator<(const DataStructures::ColourAssignment& c1, const DataStructures::ColourAssignment& c2)
{
    return c1.assignments < c2.assignments;
}

std::ostream& DataStructures::operator<<(std::ostream& out, const DataStructures::ColourAssignment& assignments)
{
    out << "[" << assignments.getColourConst(0);
    for (int i{1}; i < assignments.assignments.size(); i++)
        out << ", " << assignments.getColourConst(i);
    return out << "]";
}

