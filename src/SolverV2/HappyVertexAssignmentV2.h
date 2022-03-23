//
// Created by louis on 22/03/2022.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTEXASSIGNMENTV2_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTEXASSIGNMENTV2_H


#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include "../DataStructures/Graph/Graph.h"

namespace SolverV2
{
    enum HappinessValues{
        unknown,
        happy,
        unhappy,
        potentiallyHappy
    };

    class HappyVertexAssignmentV2
    {
    private:
        std::vector<HappinessValues> happiness{};
        std::map<HappinessValues, int> happinessValuesCounts{
            {HappinessValues::unknown, 0},
            {HappinessValues::happy, 0},
            {HappinessValues::potentiallyHappy, 0},
            {HappinessValues::unhappy, 0}
        };

    public:
        HappyVertexAssignmentV2(const HappyVertexAssignmentV2& other) = default;
        explicit HappyVertexAssignmentV2(const std::shared_ptr<DataStructures::Graph>& graph);

        void makeHappy(DataStructures::VertexType vertex);
        void makePotentiallyHappy(DataStructures::VertexType vertex);
        void makeUnhappy(DataStructures::VertexType vertex);

        [[nodiscard]] bool isUnknown(DataStructures::VertexType vertex) const;
        [[nodiscard]] bool isHappy(DataStructures::VertexType vertex) const;
        [[nodiscard]] bool isPotentiallyHappy(DataStructures::VertexType vertex) const;
        [[nodiscard]] bool isUnHappy(DataStructures::VertexType vertex) const;
        [[nodiscard]] HappinessValues getHappiness(DataStructures::VertexType vertex) const;

        [[nodiscard]] int getCountOf(HappinessValues happinessValue) const;

        friend bool operator==(const HappyVertexAssignmentV2& h1, const HappyVertexAssignmentV2& h2);
        friend bool operator<(const HappyVertexAssignmentV2& h1, const HappyVertexAssignmentV2& h2);
        friend std::ostream& operator<<(std::ostream& out, const HappyVertexAssignmentV2& happyVertexAssignment);
    };

    bool operator==(const HappyVertexAssignmentV2& h1, const HappyVertexAssignmentV2& h2);
    bool operator<(const HappyVertexAssignmentV2& h1, const HappyVertexAssignmentV2& h2);
    std::ostream& operator<<(std::ostream& out, const HappyVertexAssignmentV2& happyVertexAssignment);
    std::ostream& operator<<(std::ostream& out, const HappinessValues& happinessValues);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTEXASSIGNMENTV2_H
