//
// Created by louis on 04/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTICESTABLEENTRY_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTICESTABLEENTRY_H

#include "TableEntry.h"

#include <vector>

namespace DataStructures
{
    class HappyVerticesTableEntry : public TableEntry
    {
    public:
        class HappyVerticesAssignments
        {
        private:
            std::vector<bool> vertexIsHappy{};

        public:
            HappyVerticesAssignments(const HappyVerticesAssignments& other) = default;
            explicit HappyVerticesAssignments(const DataStructures::Graph* graph);

            void makeHappy(DataStructures::VertexType vertex);
            void makeUnhappy(DataStructures::VertexType vertex);
            [[nodiscard]] bool isHappy(DataStructures::VertexType vertex);
        };

    private:
        HappyVerticesAssignments happyVertices;

    public:
        HappyVerticesTableEntry(
                int evaluation,
                ColourAssignments& importantColourAssignments,
                HappyVerticesAssignments& happyVerticesAssignment
        );
        [[nodiscard]] HappyVerticesAssignments getHappyVertices();

        void colourGraph(DataStructures::Graph* graph) const final;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTICESTABLEENTRY_H
