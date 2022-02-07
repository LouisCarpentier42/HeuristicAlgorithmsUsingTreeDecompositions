//
// Created by louis on 06/02/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTICESASSIGNMENTS_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTICESASSIGNMENTS_H

#include "../Graph/Graph.h"

#include <ostream>
#include <vector>


namespace DataStructures
{
    class HappyVerticesAssignments
    {
    private:
        std::vector<bool> vertexIsHappy{};

    public:
        HappyVerticesAssignments(const HappyVerticesAssignments& other) = default;
        explicit HappyVerticesAssignments(const DataStructures::Graph* graph);

        void makeHappy(DataStructures::VertexType vertex);
        void makeUnhappy(DataStructures::VertexType vertex);
        [[nodiscard]] bool isHappy(DataStructures::VertexType vertex) const;

        friend bool operator==(const HappyVerticesAssignments& h1, const HappyVerticesAssignments& h2);
        friend bool operator<(const HappyVerticesAssignments& h1, const HappyVerticesAssignments& h2);
        friend std::ostream& operator<<(std::ostream& out, const HappyVerticesAssignments& assignments);
    };

    bool operator==(const HappyVerticesAssignments& h1, const HappyVerticesAssignments& h2);
    bool operator<(const HappyVerticesAssignments& h1, const HappyVerticesAssignments& h2);
    std::ostream& operator<<(std::ostream& out, const HappyVerticesAssignments& assignments);
}


#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTICESASSIGNMENTS_H
