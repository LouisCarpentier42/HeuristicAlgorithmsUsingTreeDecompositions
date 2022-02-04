//
// Created by louis on 04/02/2022.
//

#include "ExactTreeDecompositionMHV.h"
#include "../../../DataStructures/DynamicProgramming/HappyVerticesTableEntry.h"

#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>


void MaximumHappyVertices::ExactTreeDecompositionMHV::solve(
        DataStructures::Graph* graph,
        DataStructures::NiceTreeDecomposition* treeDecomposition)
{
    setProperties(graph);
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

void MaximumHappyVertices::ExactTreeDecompositionMHV::solveAtNode(DataStructures::NiceNode* node) const
{
    node->getTable()->setCapacity(std::numeric_limits<int>::max());
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
        DataStructures::HappyVerticesTableEntry::HappyVerticesAssignment happyVerticesAssignment{graph};
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

}

void MaximumHappyVertices::ExactTreeDecompositionMHV::handleForgetVertexBag(DataStructures::ForgetNode* node) const
{

}

void MaximumHappyVertices::ExactTreeDecompositionMHV::handleJoinNode(DataStructures::JoinNode* node) const
{

}

