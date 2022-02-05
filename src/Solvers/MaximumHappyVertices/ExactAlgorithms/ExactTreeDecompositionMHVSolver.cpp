//
// Created by louis on 04/02/2022.
//

#include "ExactTreeDecompositionMHV.h"
#include "../../../DataStructures/DynamicProgramming/HappyVerticesTableEntry.h"

#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>


static int POSITIVE_INFINITY = std::numeric_limits<int>::max();
static int NEGATIVE_INFINITY = std::numeric_limits<int>::min();

void MaximumHappyVertices::ExactTreeDecompositionMHV::solve(
        DataStructures::Graph* graph,
        DataStructures::NiceTreeDecomposition* treeDecomposition)
{
    setProperties(graph);
    // TODO
}

void MaximumHappyVertices::ExactTreeDecompositionMHV::solveAtNode(DataStructures::NiceNode* node) const
{
    node->getTable()->setCapacity(POSITIVE_INFINITY);
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
            handleLeafNode(dynamic_cast<DataStructures::LeafNode*>(node));
            break;
        case DataStructures::NodeType::IntroduceNode:
            handleIntroduceNode(dynamic_cast<DataStructures::IntroduceNode*>(node));
            break;
        case DataStructures::NodeType::ForgetNode:
            handleForgetVertexBag(dynamic_cast<DataStructures::ForgetNode*>(node));
            break;
        case DataStructures::NodeType::JoinNode:
            handleJoinNode(dynamic_cast<DataStructures::JoinNode*>(node));
            break;
    }
}

void MaximumHappyVertices::ExactTreeDecompositionMHV::handleLeafNode(DataStructures::LeafNode* node) const
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

    // Iterate over all the possible combinations of assigning the vertices in S to H
    std::vector<DataStructures::VertexType> S_vector{S.begin(), S.end()};
    size_t nbColours{graph->getNbColours()};
    for (int counter{0}; counter < std::pow(2, counter); counter++)
    {
        // Create the happy vertex assignment and find its evaluation
        DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments happyVerticesAssignment{graph};
        bool evalIsNegativeInfinity{false};
        int nbHappyVerticesAssignedHappy{static_cast<int>(happyVertices.size())};
        for (int i{0}; i < nbColours; ++i)
        {
            if (counter & (1<<i))
            {
                happyVerticesAssignment.makeHappy(S_vector[i]);
                if (happyVertices.find(S_vector[i]) == happyVertices.end())
                {
                    // The vertex is assigned to be happy but is not actually happy
                    evalIsNegativeInfinity = true;
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
        int evaluation;
        if (evalIsNegativeInfinity)
            evaluation = std::numeric_limits<int>::min();
        else
            evaluation = nbHappyVerticesAssignedHappy;

        // Create the partition of S
        DataStructures::TableEntry::ColourAssignments colourPartition{graph};
        for (DataStructures::VertexType vertex : S)
            colourPartition.assignColour(vertex, graph->getColour(vertex));

        node->getTable()->push(
            new DataStructures::HappyVerticesTableEntry{
                    evaluation,
                    colourPartition,
                    happyVerticesAssignment
            }
        );
    }
}

void MaximumHappyVertices::ExactTreeDecompositionMHV::handleIntroduceNode(DataStructures::IntroduceNode* node) const
{
    solveAtNode(node->getChild());

    for(DataStructures::TableEntry* entry : *node->getChild()->getTable())
    {
        auto* happyVerticesEntry = dynamic_cast<DataStructures::HappyVerticesTableEntry*>(entry);
        std::set<DataStructures::ColourType> coloursOfNeighbours{};
        std::set<DataStructures::ColourType> coloursOfHappyNeighbours{};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
        {
            coloursOfNeighbours.insert(happyVerticesEntry->getColourAssignments().getColour(neighbour));
            if (happyVerticesEntry->getHappyVertices().isHappy(neighbour))
            {
                coloursOfHappyNeighbours.insert(happyVerticesEntry->getColourAssignments().getColour(neighbour));
                if (coloursOfHappyNeighbours.size() >= 2)
                {
                    // If there are 2 neighbours happy and coloured differently, then case will always apply and
                    // the extensions will always result in an evaluation of NEGATIVE_INFINITY
                    break;
                }
            }
        }

        for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
        {
            auto hasDifferentColour = [colour](DataStructures::ColourType otherColour){ return colour != otherColour; };
            // Check case 2: if any of the neighbours is happy and has a different colour
            if (std::any_of(coloursOfHappyNeighbours.begin(), coloursOfHappyNeighbours.end(), hasDifferentColour))
            {
                DataStructures::TableEntry::ColourAssignments colourPartition_happy{happyVerticesEntry->getColourAssignments()};
                colourPartition_happy.assignColour(node->getIntroducedVertex(), colour);
                DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments happyVerticesAssignments_happy{happyVerticesEntry->getHappyVertices()};
                happyVerticesAssignments_happy.makeHappy(node->getIntroducedVertex());
                node->getTable()->push(
                    new DataStructures::HappyVerticesTableEntry{
                        NEGATIVE_INFINITY,
                        colourPartition_happy,
                        happyVerticesAssignments_happy
                    }
                );

                DataStructures::TableEntry::ColourAssignments colourPartition_unhappy{happyVerticesEntry->getColourAssignments()};
                colourPartition_unhappy.assignColour(node->getIntroducedVertex(), colour);
                DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments happyVerticesAssignments_unhappy{happyVerticesEntry->getHappyVertices()};
                happyVerticesAssignments_unhappy.makeUnhappy(node->getIntroducedVertex());
                node->getTable()->push(
                    new DataStructures::HappyVerticesTableEntry{
                        NEGATIVE_INFINITY,
                        colourPartition_unhappy,
                        happyVerticesAssignments_unhappy
                    }
                );
            }
            else
            {
                // Case 1 only prohibits the introduced vertex from being happy, thus negative extension can be added
                DataStructures::TableEntry::ColourAssignments colourPartition_unhappy{happyVerticesEntry->getColourAssignments()};
                colourPartition_unhappy.assignColour(node->getIntroducedVertex(), colour);
                DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments happyVerticesAssignments_unhappy{happyVerticesEntry->getHappyVertices()};
                happyVerticesAssignments_unhappy.makeUnhappy(node->getIntroducedVertex());
                node->getTable()->push(
                    new DataStructures::HappyVerticesTableEntry{
                        happyVerticesEntry->getEvaluation(),
                        colourPartition_unhappy,
                        happyVerticesAssignments_unhappy
                    }
                );

                // Check case 1: if any of the neighbours has a different colour
                if (std::any_of(coloursOfNeighbours.begin(), coloursOfNeighbours.end(), hasDifferentColour))
                {
                    DataStructures::TableEntry::ColourAssignments colourPartition_happy{happyVerticesEntry->getColourAssignments()};
                    colourPartition_happy.assignColour(node->getIntroducedVertex(), colour);
                    DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments happyVerticesAssignments_happy{happyVerticesEntry->getHappyVertices()};
                    happyVerticesAssignments_happy.makeHappy(node->getIntroducedVertex());
                    node->getTable()->push(
                        new DataStructures::HappyVerticesTableEntry{
                            NEGATIVE_INFINITY,
                            colourPartition_happy,
                            happyVerticesAssignments_happy
                        }
                    );
                }
                else
                {
                    DataStructures::TableEntry::ColourAssignments colourPartition_happy{happyVerticesEntry->getColourAssignments()};
                    colourPartition_happy.assignColour(node->getIntroducedVertex(), colour);
                    DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments happyVerticesAssignments_happy{happyVerticesEntry->getHappyVertices()};
                    happyVerticesAssignments_happy.makeHappy(node->getIntroducedVertex());
                    node->getTable()->push(
                        new DataStructures::HappyVerticesTableEntry{
                            happyVerticesEntry->getEvaluation() + 1,
                            colourPartition_happy,
                            happyVerticesAssignments_happy
                        }
                    );
                }
            }
        }
    }
}

void MaximumHappyVertices::ExactTreeDecompositionMHV::handleForgetVertexBag(DataStructures::ForgetNode* node) const
{

}

void MaximumHappyVertices::ExactTreeDecompositionMHV::handleJoinNode(DataStructures::JoinNode* node) const
{

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

