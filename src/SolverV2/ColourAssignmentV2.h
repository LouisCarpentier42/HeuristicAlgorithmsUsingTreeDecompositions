//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENTV2_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENTV2_H


#include <vector>
#include <memory>
#include <iostream>
#include "../DataStructures/DataStructuresAliases.h"
#include "../DataStructures/Graph/Graph.h"

namespace SolverV2
{
    class ColourAssignmentV2
    {
    private:
        std::vector<DataStructures::ColourType> colours{};

    public:
        explicit ColourAssignmentV2(const std::shared_ptr<DataStructures::Graph>& graph);
        ColourAssignmentV2(const ColourAssignmentV2& other);
        ColourAssignmentV2(
                const ColourAssignmentV2& primaryColourAssignment,
                const ColourAssignmentV2& secondaryColourAssignment);

        [[nodiscard]] DataStructures::ColourType getColour(DataStructures::VertexType vertex);
        [[nodiscard]] bool isColoured(DataStructures::VertexType vertex);

        void setColour(DataStructures::VertexType vertex, DataStructures::ColourType colour);
        void removeColour(DataStructures::VertexType vertex);

        friend bool operator==(const ColourAssignmentV2& c1, const ColourAssignmentV2& c2);
        friend bool operator<(const ColourAssignmentV2& c1, const ColourAssignmentV2& c2);
        friend std::ostream& operator<<(std::ostream& out, const ColourAssignmentV2& assignments);
    };

    bool operator==(const ColourAssignmentV2& c1, const ColourAssignmentV2& c2);
    bool operator<(const ColourAssignmentV2& c1, const ColourAssignmentV2& c2);
    std::ostream& operator<<(std::ostream& out, const ColourAssignmentV2& assignments);
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURASSIGNMENTV2_H
