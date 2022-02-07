//
// Created by louis on 06/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENTS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENTS_H

#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"
#include "HappyVerticesAssignments.h"

#include <ostream>
#include <vector>

namespace DataStructures
{
    class ColourAssignments
    {
    private:
        std::vector<DataStructures::ColourType> assignments;

    public:
        ColourAssignments(const ColourAssignments& other) = default;
        explicit ColourAssignments(const DataStructures::Graph* graph);
        ColourAssignments(const ColourAssignments& primaryColourAssignment, const ColourAssignments& secondaryColourAssignment);

        [[nodiscard]] DataStructures::VertexType getColour(DataStructures::VertexType vertex) const;
        [[nodiscard]] bool isColoured(DataStructures::VertexType vertex) const;
        void assignColour(DataStructures::VertexType vertex, DataStructures::ColourType colour);
        void removeColour(DataStructures::VertexType vertex);

        friend bool operator==(const ColourAssignments& c1, const ColourAssignments& c2);
        friend bool operator<(const ColourAssignments& c1, const ColourAssignments& c2);
        friend std::ostream& operator<<(std::ostream& out, const ColourAssignments& assignments);
    };

    bool operator==(const ColourAssignments& c1, const ColourAssignments& c2);
    bool operator<(const ColourAssignments& c1, const ColourAssignments& c2);
    std::ostream& operator<<(std::ostream& out, const ColourAssignments& assignments);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENTS_H
