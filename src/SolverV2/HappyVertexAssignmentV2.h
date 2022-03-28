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
    enum HappinessValue{
        unknown,
        happy,
        unhappy,
        potentiallyHappy
    };

    class HappyVertexAssignmentV2
    {
    private:
        std::vector<HappinessValue> happiness{};
        std::map<HappinessValue, int> happinessValuesCounts{
            {HappinessValue::unknown,          0},
            {HappinessValue::happy,            0},
            {HappinessValue::potentiallyHappy, 0},
            {HappinessValue::unhappy,          0}
        };

    public:
        explicit HappyVertexAssignmentV2(const std::shared_ptr<DataStructures::Graph>& graph);
        HappyVertexAssignmentV2(const HappyVertexAssignmentV2& other) = default;

        void setHappiness(DataStructures::VertexType vertex, HappinessValue happinessValue);
        [[nodiscard]] HappinessValue getHappiness(DataStructures::VertexType vertex) const;
        [[nodiscard]] int getCountOf(HappinessValue happinessValue) const;

        friend bool operator==(const HappyVertexAssignmentV2& h1, const HappyVertexAssignmentV2& h2);
        friend bool operator<(const HappyVertexAssignmentV2& h1, const HappyVertexAssignmentV2& h2);
        friend std::ostream& operator<<(std::ostream& out, const HappyVertexAssignmentV2& happyVertexAssignment);
    };

    bool operator==(const HappyVertexAssignmentV2& h1, const HappyVertexAssignmentV2& h2);
    bool operator<(const HappyVertexAssignmentV2& h1, const HappyVertexAssignmentV2& h2);
    std::ostream& operator<<(std::ostream& out, const HappyVertexAssignmentV2& happyVertexAssignment);
    std::ostream& operator<<(std::ostream& out, const HappinessValue& happinessValues);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_HAPPYVERTEXASSIGNMENTV2_H
