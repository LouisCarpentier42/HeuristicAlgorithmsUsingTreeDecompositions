//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHVSOLUTIONITERATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHVSOLUTIONITERATOR_H

#include "../../../DataStructures/Solution/ColourAssignment.h"
#include "../../../DataStructures/Solution/HappyVerticesAssignments.h"

#include <set>

namespace MaximumHappyVertices
{
    class ExactTreeDecompositionMHVSolutionIterator
    {
    private:
        const int nbColours;
        const std::set<DataStructures::VertexType> verticesToConsider;
        std::set<DataStructures::VertexType> verticesToColour;
        DataStructures::ColourAssignment colourAssignments;
        DataStructures::HappyVerticesAssignments happyVerticesAssignments;

        int currentColourAssignmentId{0};
        int currentHappinessAssignmentId{-1};

    public:
        ExactTreeDecompositionMHVSolutionIterator(
                std::set<DataStructures::VertexType>& verticesToConsider,
                const std::shared_ptr<DataStructures::Graph>& graph);

        [[nodiscard]] const DataStructures::ColourAssignment getColourAssignments() const;
        [[nodiscard]] const DataStructures::HappyVerticesAssignments getHappyVerticesAssignments() const;

        [[nodiscard]] bool next();
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHVSOLUTIONITERATOR_H
