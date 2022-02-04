//
// Created by louis on 17/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H

#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"

#include <map>
#include <vector>
#include <ostream>

namespace DataStructures
{
    class TableEntry
    {
    public:
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

            friend bool operator==(const TableEntry::ColourAssignments& c1, const TableEntry::ColourAssignments& c2);
            friend std::ostream& operator<<(std::ostream& out, const TableEntry::ColourAssignments& assignments);
        };

    private:
        const int evaluation;
        ColourAssignments colourAssignments;

    public:
        TableEntry(
            int evaluation,
            ColourAssignments& importantColourAssignments
        );

        [[nodiscard]] int getEvaluation() const;
        [[nodiscard]] ColourAssignments getColourAssignments() const;

        void colourGraph(DataStructures::Graph* graph) const;
    };

    bool operator==(const TableEntry::ColourAssignments& c1, const TableEntry::ColourAssignments& c2);
    std::ostream& operator<<(std::ostream& out, const TableEntry::ColourAssignments& assignments);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TABLEENTRY_H
