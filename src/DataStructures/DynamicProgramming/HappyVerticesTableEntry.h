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
        class HappyVerticesAssignment
        {
        private:
            std::vector<bool> vertexIsHappy{};

        public:
            HappyVerticesAssignment(const HappyVerticesAssignment& other) = default; // TODO needed?
            explicit HappyVerticesAssignment(const DataStructures::Graph* graph);

            void makeHappy(DataStructures::VertexType vertex);
            void makeUnhappy(DataStructures::VertexType vertex);
            [[nodiscard]] bool isHappy(DataStructures::VertexType vertex);
        };

    private:
        HappyVerticesAssignment happyVertices;

    public:
        HappyVerticesTableEntry(
            int evaluation,
            ColourAssignments& importantColourAssignments,
            HappyVerticesAssignment& happyVerticesAssignment
        );
        [[nodiscard]] HappyVerticesAssignment getHappyVertices();
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTICESTABLEENTRY_H
