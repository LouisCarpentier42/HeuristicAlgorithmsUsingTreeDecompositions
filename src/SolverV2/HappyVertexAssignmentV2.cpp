//
// Created by louis on 22/03/2022.
//

#include "HappyVertexAssignmentV2.h"

SolverV2::HappyVertexAssignmentV2::HappyVertexAssignmentV2(const std::shared_ptr<DataStructures::Graph>& graph)
    : happiness(graph->getNbVertices(), HappinessValues::unknown)
{
    happinessValuesCounts[HappinessValues::unknown] = graph->getNbVertices();
}


void SolverV2::HappyVertexAssignmentV2::makeHappy(DataStructures::VertexType vertex)
{
    happinessValuesCounts[happiness[vertex]]--;
    happinessValuesCounts[HappinessValues::happy]++;

    happiness[vertex] = HappinessValues::happy;
}

void SolverV2::HappyVertexAssignmentV2::makePotentiallyHappy(DataStructures::VertexType vertex)
{
    happinessValuesCounts[happiness[vertex]]--;
    happinessValuesCounts[HappinessValues::potentiallyHappy]++;

    happiness[vertex] = HappinessValues::potentiallyHappy;
}

void SolverV2::HappyVertexAssignmentV2::makeUnhappy(DataStructures::VertexType vertex)
{
    happinessValuesCounts[happiness[vertex]]--;
    happinessValuesCounts[HappinessValues::unhappy]++;

    happiness[vertex] = HappinessValues::unhappy;
}

bool SolverV2::HappyVertexAssignmentV2::isUnknown(DataStructures::VertexType vertex) const
{
    return happiness[vertex] == HappinessValues::unknown;;
}

bool SolverV2::HappyVertexAssignmentV2::isHappy(DataStructures::VertexType vertex) const
{
    return happiness[vertex] == HappinessValues::happy;
}

bool SolverV2::HappyVertexAssignmentV2::isPotentiallyHappy(DataStructures::VertexType vertex) const
{
    return happiness[vertex] == HappinessValues::potentiallyHappy;
}

bool SolverV2::HappyVertexAssignmentV2::isUnHappy(DataStructures::VertexType vertex) const
{
    return happiness[vertex] == HappinessValues::unhappy;
}

SolverV2::HappinessValues SolverV2::HappyVertexAssignmentV2::getHappiness(DataStructures::VertexType vertex) const
{
    return happiness[vertex];
}

int SolverV2::HappyVertexAssignmentV2::getCountOf(SolverV2::HappinessValues happinessValue) const
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

std::ostream& SolverV2::operator<<(std::ostream& out, const SolverV2::HappinessValues& happinessValue)
{
    switch(happinessValue)
    {
        case unknown: return out << ".";
        case happy: return out << "H";
        case unhappy: return out << "U";
        case potentiallyHappy: return out << "P";
    }
}

