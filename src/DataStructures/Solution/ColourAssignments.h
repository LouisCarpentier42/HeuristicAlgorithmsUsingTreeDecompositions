//
// Created by louis on 06/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENTS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENTS_H

#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"
#include "HappyVerticesAssignments.h"
#include "../TreeDecomposition/Node.h"

#include <ostream>
#include <vector>

namespace DataStructures
{
    class ColourAssignments
    {
    private:
        std::vector<DataStructures::ColourType> assignments;
        std::vector<bool> vertexKnownToBeUncoloured;
        std::vector<DataStructures::ColourAssignments*> childAssignments;

    public:
        explicit ColourAssignments(size_t size);
        explicit ColourAssignments(const DataStructures::Graph* graph);
        ColourAssignments(const DataStructures::Node* node, ColourAssignments* other);
        ColourAssignments(const DataStructures::Node* node, ColourAssignments* primaryColourAssignment, ColourAssignments* secondaryColourAssignment);

        [[nodiscard]] size_t getSize() const;
        [[nodiscard]] DataStructures::ColourType getColour(DataStructures::VertexType vertex);
        [[nodiscard]] DataStructures::ColourType getColour(const DataStructures::VertexType& vertex) const;
        [[nodiscard]] bool isColoured(DataStructures::VertexType vertex);
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
