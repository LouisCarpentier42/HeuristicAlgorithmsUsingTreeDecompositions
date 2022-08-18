//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGITERATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGITERATOR_H

#include "SolutionIterator.h"
#include "../../DataStructures/Solution/ColourAssignment.h"

#include <set>

namespace Solvers
{
    class ColouringIterator : public SolutionIterator<DataStructures::ColourAssignment>
    {
    private:
        const int nbColours;
        const std::set<DataStructures::VertexType> verticesToConsider;
        std::set<DataStructures::VertexType> verticesToColour;
        DataStructures::ColourAssignment colourAssignments;
        int currentColourAssignmentId{0};

    public:
        ColouringIterator(std::set<DataStructures::VertexType> verticesToConsider, std::shared_ptr<DataStructures::Graph>& graph);

        [[nodiscard]] const DataStructures::ColourAssignment getValue() const override;

        [[nodiscard]] bool next() override;
    };
}




#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGITERATOR_H
