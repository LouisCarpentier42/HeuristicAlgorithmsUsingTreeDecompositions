//
// Created by louis on 04/02/2022.
//

#include "ExactTreeDecompositionMHV.h"
#include "ExactTreeDecompositionSolutionIterator.h"

#include <algorithm>
#include <cmath>
#include <vector>

int MaximumHappyVertices::ExactTreeDecompositionMHV::solve(
        DataStructures::Graph* graph,
        DataStructures::NiceTreeDecomposition* treeDecomposition)
{
    setProperties(graph);
    ExactTreeDecompositionRanking rankingRoot = solveAtNode(treeDecomposition->getRoot());
    return rankingRoot.getBestEvaluation();
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
    for (int counter{0}; counter < std::pow(2, nbColours); counter++)
    {
        // Create the partition of S for the colours
        DataStructures::ColourAssignments colourAssignments{graph};
        for (DataStructures::VertexType vertex : S)
            colourAssignments.assignColour(vertex, graph->getColour(vertex));

        // Create the happy vertex assignment and find its evaluation
        DataStructures::HappyVerticesAssignments happyVerticesAssignments{graph};
        int numberToConvert{counter};
        bool illegalHappyVertexAssignment{false};
        int nbHappyVerticesAssignedHappy{static_cast<int>(happyVertices.size())};
        for (DataStructures::VertexType vertex : S)
        {
            if ((numberToConvert % 2) == 1)
            {
                happyVerticesAssignments.makeHappy(vertex);
                if (happyVertices.find(vertex) == happyVertices.end())
                {
                    // The vertex is assigned to be happy but is not actually happy
                    illegalHappyVertexAssignment = true;
                }
            }
            else
            {
                happyVerticesAssignments.makeUnhappy(vertex);
                if (happyVertices.find(vertex) != happyVertices.end())
                {
                    // The vertex can still be happy but isn't assigned to be happy
                    nbHappyVerticesAssignedHappy -= 1;
                }
            }
            numberToConvert /= 2;
        }

        if (!illegalHappyVertexAssignment)
        {
            ranking.addSolution(nbHappyVerticesAssignedHappy, colourAssignments, happyVerticesAssignments);
        }

    }
    return ranking;
}

MaximumHappyVertices::ExactTreeDecompositionRanking MaximumHappyVertices::ExactTreeDecompositionMHV::handleIntroduceNode(DataStructures::IntroduceNode* node) const
{
    // Solve for child
    ExactTreeDecompositionRanking rankingChild = solveAtNode(node->getChild());

    if (S.find(node->getIntroducedVertex()) != S.end())
        return rankingChild;

    // Gather all vertices that should be coloured, that is the vertices in S and the vertices in the bag
    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

    // Iterate over all the solutions
    ExactTreeDecompositionRanking ranking{};
    ExactTreeDecompositionSolutionIterator iterator{verticesToConsider, graph};
    while (iterator.next())
    {
        DataStructures::ColourAssignments colourAssignments{iterator.getColourAssignments()};
        DataStructures::HappyVerticesAssignments happyVerticesAssignments{iterator.getHappyVerticesAssignments()};

        std::set<DataStructures::ColourType> otherColoursOfNeighbours{};
        std::set<DataStructures::ColourType> otherColoursOfHappyNeighbours{};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
        {
            if (!colourAssignments.isColoured(neighbour))
                continue;

            if (colourAssignments.getColour(neighbour) != colourAssignments.getColour(node->getIntroducedVertex()))
            {
                otherColoursOfNeighbours.insert(colourAssignments.getColour(neighbour));
                if (happyVerticesAssignments.isHappy(neighbour))
                {
                    otherColoursOfHappyNeighbours.insert(colourAssignments.getColour(neighbour));
                    break;
                }
            }
        }

        // Case 1
        if (!otherColoursOfNeighbours.empty() && happyVerticesAssignments.isHappy(node->getIntroducedVertex()))
            continue;

        // Case 2
        if (!otherColoursOfHappyNeighbours.empty())
            continue;

        DataStructures::ColourAssignments colourAssignmentsChild{colourAssignments};
        colourAssignmentsChild.removeColour(node->getIntroducedVertex());
        DataStructures::HappyVerticesAssignments happyVerticesAssignmentsChild{happyVerticesAssignments};
        happyVerticesAssignmentsChild.makeUnhappy(node->getIntroducedVertex());

        int evaluationChild{rankingChild.getEvaluation(colourAssignmentsChild, happyVerticesAssignmentsChild)};
        if (evaluationChild == ExactTreeDecompositionRanking::NEGATIVE_INFINITY)
            continue;

        if (happyVerticesAssignments.isHappy(node->getIntroducedVertex()))
        {
            ranking.addSolution(evaluationChild + 1, colourAssignments, happyVerticesAssignments);
        }
        else
        {
            ranking.addSolution(evaluationChild, colourAssignments, happyVerticesAssignments);
        }
    }
    return ranking;
}

MaximumHappyVertices::ExactTreeDecompositionRanking MaximumHappyVertices::ExactTreeDecompositionMHV::handleForgetVertexBag(DataStructures::ForgetNode* node) const
{
    // Solve for child
    ExactTreeDecompositionRanking rankingChild = solveAtNode(node->getChild());

    if (S.find(node->getForgottenVertex()) != S.end())
        return rankingChild;

    // Gather all vertices that should be coloured, that is the vertices in S and the vertices in the bag
    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

    // Iterate over all the solutions
    ExactTreeDecompositionRanking ranking{};
    ExactTreeDecompositionSolutionIterator iterator{verticesToConsider, graph};
    while (iterator.next())
    {
        DataStructures::ColourAssignments colourAssignments{iterator.getColourAssignments()};
        DataStructures::HappyVerticesAssignments happyVerticesAssignments{iterator.getHappyVerticesAssignments()};
        int evaluation{ExactTreeDecompositionRanking::NEGATIVE_INFINITY};
        for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
        {
            colourAssignments.assignColour(node->getForgottenVertex(), colour);

            happyVerticesAssignments.makeHappy(node->getForgottenVertex());
            int evaluationHappy{rankingChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
            if (evaluationHappy > evaluation)
                evaluation = evaluationHappy;

            happyVerticesAssignments.makeUnhappy(node->getForgottenVertex());
            int evaluationUnhappy{rankingChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
            if (evaluationUnhappy > evaluation)
                evaluation = evaluationUnhappy;
        }

        colourAssignments.removeColour(node->getForgottenVertex());
        happyVerticesAssignments.makeUnhappy(node->getForgottenVertex());
        if (evaluation > ExactTreeDecompositionRanking::NEGATIVE_INFINITY)
        {
            ranking.addSolution(evaluation, colourAssignments, happyVerticesAssignments);
        }
    }
    return ranking;
}

MaximumHappyVertices::ExactTreeDecompositionRanking MaximumHappyVertices::ExactTreeDecompositionMHV::handleJoinNode(DataStructures::JoinNode* node) const
{
    // Solve for the children
    ExactTreeDecompositionRanking rankingLeftChild = solveAtNode(node->getLeftChild());
    ExactTreeDecompositionRanking rankingRightChild = solveAtNode(node->getRightChild());

    // Gather all vertices that should be coloured, that is the vertices in S and the vertices in the bag
    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

    // Iterate over all the solutions
    ExactTreeDecompositionRanking ranking{};
    ExactTreeDecompositionSolutionIterator iterator{verticesToConsider, graph};
    while (iterator.next())
    {
        DataStructures::ColourAssignments colourAssignments{iterator.getColourAssignments()};
        DataStructures::HappyVerticesAssignments happyVerticesAssignments{iterator.getHappyVerticesAssignments()};

        int evaluationLeftChild{rankingLeftChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
        if (evaluationLeftChild == ExactTreeDecompositionRanking::NEGATIVE_INFINITY)
            continue;

        int evaluationRightChild{rankingRightChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
        if (evaluationRightChild == ExactTreeDecompositionRanking::NEGATIVE_INFINITY)
            continue;

        int nbVerticesCountedDouble{0};
        for (DataStructures::VertexType vertex : verticesToConsider)
        {
            if (happyVerticesAssignments.isHappy(vertex))
                nbVerticesCountedDouble++;
        }

        ranking.addSolution(
            evaluationLeftChild + evaluationRightChild - nbVerticesCountedDouble,
            colourAssignments,
            happyVerticesAssignments
        );
    }
    return ranking;
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
