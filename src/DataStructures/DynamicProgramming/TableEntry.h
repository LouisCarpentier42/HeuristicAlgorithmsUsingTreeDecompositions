//
// Created by louis on 17/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H

#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"
#include "../Solution/ColourAssignments.h"

#include <map>
#include <vector>

namespace DataStructures
{
    class TableEntry
    {
    private:
        const int evaluation;
        const ColourAssignments colourAssignments;

    public:
        TableEntry(
            int evaluation,
            const ColourAssignments& colourAssignments
        );

        [[nodiscard]] int getEvaluation() const;
        [[nodiscard]] ColourAssignments getColourAssignments() const;

        void colourGraph(DataStructures::Graph* graph) const;

        friend bool operator<(const TableEntry& entry1, const TableEntry& entry2);
    };

    bool operator<(const TableEntry& entry1, const TableEntry& entry2);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H
