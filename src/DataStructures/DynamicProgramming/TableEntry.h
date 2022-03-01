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
        ColourAssignments colourAssignments;

    public:
        TableEntry(
            int evaluation,
            ColourAssignments& colourAssignments
        );

        [[nodiscard]] int getEvaluation() const;
        [[nodiscard]] ColourAssignments* getColourAssignments();

        void colourGraph(DataStructures::Graph* graph);

        friend bool operator<(TableEntry& entry1, TableEntry& entry2);
    };

    bool operator<(TableEntry& entry1, TableEntry& entry2);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H
