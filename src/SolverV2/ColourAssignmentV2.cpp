//
// Created by louis on 22/03/2022.
//

#include "ColourAssignmentV2.h"

SolverV2::ColourAssignmentV2::ColourAssignmentV2(const std::shared_ptr<DataStructures::Graph>& graph)
    : colours(graph->getNbVertices(), 0)
{ }

SolverV2::ColourAssignmentV2::ColourAssignmentV2(const SolverV2::ColourAssignmentV2& other) = default;

SolverV2::ColourAssignmentV2::ColourAssignmentV2(
        const SolverV2::ColourAssignmentV2& primaryColourAssignment,
        const SolverV2::ColourAssignmentV2& secondaryColourAssignment)
    : colours{primaryColourAssignment.colours}
{
    for (DataStructures::VertexType vertex{0}; vertex < colours.size(); vertex++)
    {
        if (!isColoured(vertex))
            setColour(vertex, secondaryColourAssignment.colours[vertex]);
    }
}


DataStructures::ColourType SolverV2::ColourAssignmentV2::getColour(DataStructures::VertexType vertex)
{
    return colours[vertex];
}

bool SolverV2::ColourAssignmentV2::isColoured(DataStructures::VertexType vertex)
{
    return getColour(vertex) != 0;
}

void SolverV2::ColourAssignmentV2::setColour(DataStructures::VertexType vertex, DataStructures::ColourType colour)
{
    colours[vertex] = colour;
}

void SolverV2::ColourAssignmentV2::removeColour(DataStructures::VertexType vertex)
{
    colours[vertex] = 0;
}

bool SolverV2::operator==(const SolverV2::ColourAssignmentV2& c1, const SolverV2::ColourAssignmentV2& c2)
{
    return c1.colours == c2.colours;
}

bool SolverV2::operator<(const SolverV2::ColourAssignmentV2& c1, const SolverV2::ColourAssignmentV2& c2)
{
    return c1.colours < c2.colours;
}

std::ostream &SolverV2::operator<<(std::ostream& out, const SolverV2::ColourAssignmentV2& colourAssignment)
{
    out << "[" << colourAssignment.colours[0];
    for (int i{1}; i < colourAssignment.colours.size(); i++)
        std::cout << ", " << colourAssignment.colours[i];
    return out << "]";
}
