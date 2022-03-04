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
        explicit ColourAssignments(const DataStructures::Graph* graph);
        ColourAssignments(const DataStructures::Node* node, ColourAssignments* other);
        ColourAssignments(const DataStructures::Node* node, ColourAssignments* primaryColourAssignment, ColourAssignments* secondaryColourAssignment);

        [[nodiscard]] DataStructures::VertexType getColour(DataStructures::VertexType vertex);
        [[nodiscard]] DataStructures::VertexType getColour(const DataStructures::VertexType& vertex) const;
        [[nodiscard]] bool isColoured(DataStructures::VertexType vertex);
        void assignColour(DataStructures::VertexType vertex, DataStructures::ColourType colour);
        void removeColour(DataStructures::VertexType vertex);

        friend bool operator==(const ColourAssignments& c1, const ColourAssignments& c2); // TODO mag probs weg (+ functie hieronder) (+ in happy vertex assignment)
        friend bool operator<(const ColourAssignments& c1, const ColourAssignments& c2);
        friend std::ostream& operator<<(std::ostream& out, ColourAssignments& assignments);
    };

    bool operator==(const ColourAssignments& c1, const ColourAssignments& c2);
    bool operator<(const ColourAssignments& c1, const ColourAssignments& c2);
    std::ostream& operator<<(std::ostream& out, ColourAssignments& assignments);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENTS_H
