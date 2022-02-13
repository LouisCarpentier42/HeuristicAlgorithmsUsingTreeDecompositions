//
// Created by louis on 13/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGITERATOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGITERATOR_H

#include "SolutionIterator.h"
#include "../../DataStructures/Solution/ColourAssignments.h"

#include <set>

namespace Solvers
{
    class ColouringIterator : public SolutionIterator<DataStructures::ColourAssignments>
    {
    private:
        const int nbColours;
        const std::set<DataStructures::VertexType> verticesToConsider;
        std::set<DataStructures::VertexType> verticesToColour;
        DataStructures::ColourAssignments colourAssignments;
        int currentColourAssignmentId{0};

    public:
        ColouringIterator(std::set<DataStructures::VertexType> verticesToConsider, DataStructures::Graph* graph);

        [[nodiscard]] const DataStructures::ColourAssignments getValue() const override;

        [[nodiscard]] bool next() override;
    };
}




#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURINGITERATOR_H
