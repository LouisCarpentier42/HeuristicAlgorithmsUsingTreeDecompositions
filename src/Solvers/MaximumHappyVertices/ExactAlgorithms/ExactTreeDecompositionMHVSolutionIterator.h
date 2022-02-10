//
// Created by louis on 07/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHVSOLUTIONITERATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHVSOLUTIONITERATOR_H

#include "../../../DataStructures/Solution/ColourAssignments.h"
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
        DataStructures::ColourAssignments colourAssignments;
        DataStructures::HappyVerticesAssignments happyVerticesAssignments;

        int currentColourAssignmentId{0};
        int currentHappinessAssignmentId{-1};

    public:
        ExactTreeDecompositionMHVSolutionIterator(std::set<DataStructures::VertexType> verticesToConsider, DataStructures::Graph* graph);

        [[nodiscard]] const DataStructures::ColourAssignments getColourAssignments() const;
        [[nodiscard]] const DataStructures::HappyVerticesAssignments getHappyVerticesAssignments() const;

        [[nodiscard]] bool next();
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXACTTREEDECOMPOSITIONMHVSOLUTIONITERATOR_H
