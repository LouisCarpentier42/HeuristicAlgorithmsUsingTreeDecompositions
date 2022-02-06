//
// Created by louis on 04/02/2022.
//

#include "ExactTreeDecompositionMHV.h"

#include <algorithm>
#include <cmath>
#include <vector>


void MaximumHappyVertices::ExactTreeDecompositionMHV::solve(
        DataStructures::Graph* graph,
        DataStructures::NiceTreeDecomposition* treeDecomposition)
{
    setProperties(graph);
    // TODO finish method
}

MaximumHappyVertices::ExactTreeDecompositionRanking MaximumHappyVertices::ExactTreeDecompositionMHV::solveAtNode(DataStructures::NiceNode* node) const
{
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
            return handleLeafNode(dynamic_cast<DataStructures::LeafNode*>(node));
        case DataStructures::NodeType::IntroduceNode:
            return handleIntroduceNode(dynamic_cast<DataStructures::IntroduceNode*>(node));
        case DataStructures::NodeType::ForgetNode:
            return handleForgetVertexBag(dynamic_cast<DataStructures::ForgetNode*>(node));
        case DataStructures::NodeType::JoinNode:
            return handleJoinNode(dynamic_cast<DataStructures::JoinNode*>(node));
    }
}

MaximumHappyVertices::ExactTreeDecompositionRanking MaximumHappyVertices::ExactTreeDecompositionMHV::handleLeafNode(DataStructures::LeafNode* node) const
{
    // Find the set of vertices that are happy
    std::set<DataStructures::VertexType> happyVertices{};
    for (DataStructures::VertexType vertex : S)
    {
        bool noneEmptyIntersection = std::any_of(
                graph->getNeighbours(vertex).begin(),
                graph->getNeighbours(vertex).end(),
                [this](DataStructures::VertexType neighbour){return S.find(neighbour) != S.end(); });
        // If the neighbours and S have a none-empty intersection, then one of the neighbours
        // of vertex has a different colour since all the vertices in S have a different colour
        if (!noneEmptyIntersection)
            happyVertices.insert(vertex);
    }

    // Variable to push all the solutions to
    MaximumHappyVertices::ExactTreeDecompositionRanking ranking{};

    // Iterate over all the possible combinations of assigning the vertices in S to H
    std::vector<DataStructures::VertexType> S_vector{S.begin(), S.end()};
    size_t nbColours{graph->getNbColours()};
    for (int counter{0}; counter < std::pow(2, counter); counter++)
    {
        // Create the partition of S for the colours
        DataStructures::ColourAssignments colourPartition{graph};
        for (DataStructures::VertexType vertex : S)
            colourPartition.assignColour(vertex, graph->getColour(vertex));

        // Create the happy vertex assignment and find its evaluation
        DataStructures::HappyVerticesAssignments happyVerticesAssignment{graph};
        bool illegalHappyVertexAssignment{false};
        int nbHappyVerticesAssignedHappy{static_cast<int>(happyVertices.size())};
        for (int i{0}; i < nbColours; ++i)
        {
            if (counter & (1<<i))
            {
                happyVerticesAssignment.makeHappy(S_vector[i]);
                if (happyVertices.find(S_vector[i]) == happyVertices.end())
                {
                    // The vertex is assigned to be happy but is not actually happy
                    illegalHappyVertexAssignment = true;
                }
            }
            else
            {
                if (happyVertices.find(S_vector[i]) != happyVertices.end())
                {
                    // The vertex can still be happy but isn't assigned to be happy
                    nbHappyVerticesAssignedHappy -= 1;
                }
            }
        }

        if (!illegalHappyVertexAssignment)
            ranking.addSolution(nbHappyVerticesAssignedHappy, colourPartition, happyVerticesAssignment);
    }
    return ranking;
}

MaximumHappyVertices::ExactTreeDecompositionRanking MaximumHappyVertices::ExactTreeDecompositionMHV::handleIntroduceNode(DataStructures::IntroduceNode* node) const
{
    // TODO do something else if the vertex is precoloured?
    ExactTreeDecompositionRanking rankingChild = solveAtNode(node->getChild());
    ExactTreeDecompositionRanking ranking{};

    for (const auto& it : rankingChild)
    {
        DataStructures::ColourAssignments colourAssignments = it.first.first;
        DataStructures::HappyVerticesAssignments happyVerticesAssignments = it.first.second;
        int evaluation = it.second;

        std::set<DataStructures::ColourType> coloursOfNeighbours{};
        std::set<DataStructures::ColourType> coloursOfHappyNeighbours{};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
        {
            if (colourAssignments.isColoured(neighbour))
            {
                coloursOfNeighbours.insert(colourAssignments.getColour(neighbour));
                if (happyVerticesAssignments.isHappy(neighbour))
                {
                    coloursOfHappyNeighbours.insert(colourAssignments.getColour(neighbour));
                    if (coloursOfHappyNeighbours.size() >= 2)
                    {
                        // If there are 2 neighbours happy and coloured differently, then case 2 will always apply and
                        // the extensions will always result in an evaluation of NEGATIVE_INFINITY
                        break;
                    }
                }
            }
        }

        if (coloursOfHappyNeighbours.size() >= 2)
        {
            // Case 2 will always apply
            continue;
        }
        else if (coloursOfHappyNeighbours.size() == 1)
        {
            // Case 2 applies for all colours except the colour of the happy neighbour
            DataStructures::ColourType colour{*coloursOfHappyNeighbours.begin()};

            // Making the introduced vertex unhappy will is always possible
            DataStructures::ColourAssignments colourPartition_unhappy{colourAssignments};
            colourPartition_unhappy.assignColour(node->getIntroducedVertex(), colour);
            DataStructures::HappyVerticesAssignments happyVerticesAssignments_unhappy{happyVerticesAssignments};
            happyVerticesAssignments_unhappy.makeUnhappy(node->getIntroducedVertex());
            ranking.addSolution(evaluation, colourPartition_unhappy, happyVerticesAssignments_unhappy);

            // Case 1: The introduced vertex can only be assigned happy if it doesn't have a differently coloured neighbour
            bool hasDifferentlyColouredNeighbour{
                std::any_of(
                    coloursOfNeighbours.begin(),
                    coloursOfNeighbours.end(),
                    [colour](DataStructures::ColourType otherColour){ return colour != otherColour; }
                )
            };
            if (!hasDifferentlyColouredNeighbour)
            {
                DataStructures::ColourAssignments colourPartition_happy{colourAssignments};
                colourPartition_happy.assignColour(node->getIntroducedVertex(), colour);
                DataStructures::HappyVerticesAssignments happyVerticesAssignments_happy{happyVerticesAssignments};
                happyVerticesAssignments_happy.makeHappy(node->getIntroducedVertex());
                ranking.addSolution(evaluation, colourPartition_happy, happyVerticesAssignments_happy);
            }
        }
        else
        {
            for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
            {
                // Making the introduced vertex unhappy will is always possible
                DataStructures::ColourAssignments colourPartition_unhappy{colourAssignments};
                colourPartition_unhappy.assignColour(node->getIntroducedVertex(), colour);
                DataStructures::HappyVerticesAssignments happyVerticesAssignments_unhappy{happyVerticesAssignments};
                happyVerticesAssignments_unhappy.makeUnhappy(node->getIntroducedVertex());
                ranking.addSolution(evaluation, colourPartition_unhappy, happyVerticesAssignments_unhappy);

                // Case 1: The introduced vertex can only be assigned happy if it doesn't have a differently coloured neighbour
                bool hasDifferentlyColouredNeighbour{
                    std::any_of(
                        coloursOfNeighbours.begin(),
                        coloursOfNeighbours.end(),
                        [colour](DataStructures::ColourType otherColour){ return colour != otherColour; }
                    )
                };
                if (!hasDifferentlyColouredNeighbour)
                {
                    DataStructures::ColourAssignments colourPartition_happy{colourAssignments};
                    colourPartition_happy.assignColour(node->getIntroducedVertex(), colour);
                    DataStructures::HappyVerticesAssignments happyVerticesAssignments_happy{happyVerticesAssignments};
                    happyVerticesAssignments_happy.makeHappy(node->getIntroducedVertex());
                    ranking.addSolution(evaluation, colourPartition_happy, happyVerticesAssignments_happy);
                }
            }
        }
    }
}

MaximumHappyVertices::ExactTreeDecompositionRanking MaximumHappyVertices::ExactTreeDecompositionMHV::handleForgetVertexBag(DataStructures::ForgetNode* node) const
{
    // Uncolour vertex!
    ExactTreeDecompositionRanking rankingChild = solveAtNode(node->getChild());
}

MaximumHappyVertices::ExactTreeDecompositionRanking MaximumHappyVertices::ExactTreeDecompositionMHV::handleJoinNode(DataStructures::JoinNode* node) const
{
    ExactTreeDecompositionRanking rankingLeftChild = solveAtNode(node->getLeftChild());
    ExactTreeDecompositionRanking rankingRightChild = solveAtNode(node->getRightChild());
}

void MaximumHappyVertices::ExactTreeDecompositionMHV::setProperties(DataStructures::Graph* graph)
{
    this->graph = graph;
    S.clear();
    std::vector<bool> coloursUsed(graph->getNbColours()+1, false);
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (graph->isPrecoloured(vertex) && !coloursUsed[graph->getColour(vertex)])
        {
            coloursUsed[graph->getColour(vertex)] = true;
            S.insert(vertex);
        }
    }
}

