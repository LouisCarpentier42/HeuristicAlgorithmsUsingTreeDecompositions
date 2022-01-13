//
// Created by louis on 17/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H

#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"

#include <map>
#include <vector>

namespace DataStructures
{
    class TableEntry
    {
    public:
        using NextEntries = std::vector<TableEntry*>; // TODO needed?
        class ColourAssignments
        {
        private:
            std::vector<DataStructures::ColourType> assignments;

        public:
            ColourAssignments(const ColourAssignments& other) = default;
            explicit ColourAssignments(const DataStructures::Graph* graph);
            ColourAssignments(const ColourAssignments& primaryColourAssignment, const ColourAssignments& secondaryColourAssignment);

            [[nodiscard]] DataStructures::VertexType getColour(DataStructures::VertexType vertex) const;
            [[nodiscard]] bool isColoured(DataStructures::VertexType vertex) const;
            void assignColour(DataStructures::VertexType vertex, DataStructures::ColourType colour);
        };

    private:
        const int evaluation;
        NextEntries nextEntries;
        ColourAssignments colourAssignments;

    public:
        TableEntry(
            int evaluation,
            NextEntries nextEntries,
            ColourAssignments& importantColourAssignments
        );

        [[nodiscard]] int getEvaluation() const;
        [[nodiscard]] ColourAssignments getColourAssignments() const;

        void colourGraph(DataStructures::Graph* graph) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H
