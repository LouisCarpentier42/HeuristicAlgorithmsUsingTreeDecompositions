//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H

#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"
#include "../Solution/ColourAssignment.h"

#include <map>
#include <vector>
#include <memory>

namespace DataStructures
{
    class TableEntry
    {
    private:
        const int evaluation;
        std::shared_ptr<ColourAssignment> colourAssignments;

    public:
        TableEntry(
            int evaluation,
            std::shared_ptr<ColourAssignment>& colourAssignments
        );

        [[nodiscard]] int getEvaluation() const;
        [[nodiscard]] std::shared_ptr<ColourAssignment> getColourAssignments();

        void colourGraph(std::shared_ptr<Graph>& graph);

        friend bool operator<(const TableEntry& entry1, const TableEntry& entry2);
    };

    bool operator<(const TableEntry& entry1, const TableEntry& entry2);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H
