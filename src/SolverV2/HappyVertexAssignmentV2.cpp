//
// Created by louis on 22/03/2022.
//

#include "HappyVertexAssignmentV2.h"

SolverV2::HappyVertexAssignmentV2::HappyVertexAssignmentV2(const std::shared_ptr<DataStructures::Graph>& graph)
    : happiness(graph->getNbVertices(), HappinessValue::unknown)
{
    happinessValuesCounts[HappinessValue::unknown] = graph->getNbVertices();
}

void SolverV2::HappyVertexAssignmentV2::setHappiness(
        DataStructures::VertexType vertex,
        SolverV2::HappinessValue happinessValue)
{
    happinessValuesCounts[happiness[vertex]]--;
    happinessValuesCounts[happinessValue]++;

    happiness[vertex] = happinessValue;
}

SolverV2::HappinessValue SolverV2::HappyVertexAssignmentV2::getHappiness(DataStructures::VertexType vertex) const
{
    return happiness.at(vertex);
}

int SolverV2::HappyVertexAssignmentV2::getCountOf(SolverV2::HappinessValue happinessValue) const
{
    return happinessValuesCounts.at(happinessValue);
}

bool SolverV2::operator==(const SolverV2::HappyVertexAssignmentV2& h1, const SolverV2::HappyVertexAssignmentV2& h2)
{
    return h1.happiness == h2.happiness;
}

bool SolverV2::operator<(const SolverV2::HappyVertexAssignmentV2 &h1, const SolverV2::HappyVertexAssignmentV2 &h2)
{
    return h1.happiness < h2.happiness;
}

std::ostream& SolverV2::operator<<(std::ostream& out, const SolverV2::HappyVertexAssignmentV2& happyVertexAssignment)
{
    out << "[" << happyVertexAssignment.happiness[0];
    for (int i{1}; i < happyVertexAssignment.happiness.size(); i++)
        out << ", " << happyVertexAssignment.happiness[i];
    return out << "]";
}

std::ostream& SolverV2::operator<<(std::ostream& out, const SolverV2::HappinessValue& happinessValue)
{
    switch(happinessValue)
    {
        case unknown: return out << ".";
        case happy: return out << "H";
        case unhappy: return out << "U";
        case potentiallyHappy: return out << "P";
    }
}

