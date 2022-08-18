//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENT_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENT_H

#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"
#include "HappyVerticesAssignments.h"
#include "../TreeDecomposition/Node.h"

#include <memory>
#include <ostream>
#include <vector>

namespace DataStructures
{
    class ColourAssignment
    {
    private:
        std::vector<ColourType> assignments;
        std::vector<bool> vertexKnownToBeUncoloured;
        std::vector<std::shared_ptr<ColourAssignment>> childAssignments;

    public:
        explicit ColourAssignment(size_t size);
        explicit ColourAssignment(const std::shared_ptr<Graph>& graph);
        ColourAssignment(
            const std::shared_ptr<Node>& node,
            const std::shared_ptr<ColourAssignment>& other);
        ColourAssignment(
            const std::shared_ptr<Node>& node,
            const std::shared_ptr<ColourAssignment>& primaryColourAssignment,
            const std::shared_ptr<ColourAssignment>& secondaryColourAssignment);

        [[nodiscard]] size_t getSize() const;
        [[nodiscard]] ColourType getColour(VertexType vertex);
        [[nodiscard]] ColourType getColourConst(const VertexType& vertex) const;
        [[nodiscard]] bool isColoured(VertexType vertex);
        [[nodiscard]] bool isColouredConst(VertexType vertex) const;
        void assignColour(VertexType vertex, ColourType colour);
        void removeColour(VertexType vertex);

        friend bool operator==(const ColourAssignment& c1, const ColourAssignment& c2);
        friend bool operator<(const ColourAssignment& c1, const ColourAssignment& c2);
        friend std::ostream& operator<<(std::ostream& out, const ColourAssignment& assignments);
    };

    bool operator==(const ColourAssignment& c1, const ColourAssignment& c2);
    bool operator<(const ColourAssignment& c1, const ColourAssignment& c2);
    std::ostream& operator<<(std::ostream& out, const ColourAssignment& assignments);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENT_H
