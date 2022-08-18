//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "ExactTreeDecompositionMHV.h"
#include "ExactTreeDecompositionMHVSolutionIterator.h"

#include <algorithm>
#include <cmath>
#include <vector>


void MaximumHappyVertices::ExactTreeDecompositionMHV::setProperties(std::shared_ptr<DataStructures::Graph>& graph)
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

Solvers::ExactTreeDecompositionRankingMHV MaximumHappyVertices::ExactTreeDecompositionMHV::handleLeafNode(
        std::shared_ptr<DataStructures::LeafNode>& node) const
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
    Solvers::ExactTreeDecompositionRankingMHV ranking{};

    // Iterate over all the possible combinations of assigning the vertices in S to H
    std::vector<DataStructures::VertexType> S_vector{S.begin(), S.end()};
    size_t nbColours{graph->getNbColours()};
    for (int counter{0}; counter < std::pow(2, nbColours); counter++)
    {
        // Create the partition of S for the colours
        DataStructures::ColourAssignment colourAssignments{graph};
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
            ranking.addSolution(nbHappyVerticesAssignedHappy, colourAssignments, happyVerticesAssignments, {});
        }
    }
    return ranking;
}

Solvers::ExactTreeDecompositionRankingMHV MaximumHappyVertices::ExactTreeDecompositionMHV::handleIntroduceNode(
        std::shared_ptr<DataStructures::IntroduceNode>& node,
        const Solvers::ExactTreeDecompositionRankingMHV& rankingChild) const
{
    if (S.find(node->getIntroducedVertex()) != S.end())
        return rankingChild;

    // Gather all vertices that should be coloured, that is the vertices in S and the vertices in the bag
    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

    // Iterate over all the solutions
    Solvers::ExactTreeDecompositionRankingMHV ranking{};
    ExactTreeDecompositionMHVSolutionIterator iterator{verticesToConsider, graph};
    while (iterator.next())
    {
        DataStructures::ColourAssignment colourAssignments{iterator.getColourAssignments()};
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

        DataStructures::ColourAssignment colourAssignmentsChild{colourAssignments};
        colourAssignmentsChild.removeColour(node->getIntroducedVertex());
        DataStructures::HappyVerticesAssignments happyVerticesAssignmentsChild{happyVerticesAssignments};
        happyVerticesAssignmentsChild.makeUnhappy(node->getIntroducedVertex());

        int evaluationChild{rankingChild.getEvaluation(colourAssignmentsChild, happyVerticesAssignmentsChild)};
        if (evaluationChild == Solvers::ExactTreeDecompositionRankingMHV::NEGATIVE_INFINITY)
            continue;

        std::shared_ptr<DataStructures::ColourAssignment> fullColouringChild = rankingChild.getFullColouring(colourAssignmentsChild, happyVerticesAssignmentsChild);
        if (happyVerticesAssignments.isHappy(node->getIntroducedVertex()))
        {
            ranking.addSolution(evaluationChild + 1, colourAssignments, happyVerticesAssignments, {fullColouringChild});
        }
        else
        {
            ranking.addSolution(evaluationChild, colourAssignments, happyVerticesAssignments, {fullColouringChild});
        }
    }
    return ranking;
}

Solvers::ExactTreeDecompositionRankingMHV MaximumHappyVertices::ExactTreeDecompositionMHV::handleForgetNode(
        std::shared_ptr<DataStructures::ForgetNode>& node,
        const Solvers::ExactTreeDecompositionRankingMHV& rankingChild) const
{
    if (S.find(node->getForgottenVertex()) != S.end())
        return rankingChild;

    // Gather all vertices that should be coloured, that is the vertices in S and the vertices in the bag
    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

    // Iterate over all the solutions
    Solvers::ExactTreeDecompositionRankingMHV ranking{};
    ExactTreeDecompositionMHVSolutionIterator iterator{verticesToConsider, graph};
    while (iterator.next())
    {
        DataStructures::ColourAssignment colourAssignments{iterator.getColourAssignments()};
        DataStructures::HappyVerticesAssignments happyVerticesAssignments{iterator.getHappyVerticesAssignments()};
        int evaluation{Solvers::ExactTreeDecompositionRankingMHV::NEGATIVE_INFINITY};
        DataStructures::ColourType colourInBestChild{0};
        bool isHappyInBestChild{false};
        for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
        {
            colourAssignments.assignColour(node->getForgottenVertex(), colour);

            happyVerticesAssignments.makeHappy(node->getForgottenVertex());
            int evaluationHappy{rankingChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
            if (evaluationHappy > evaluation)
            {
                evaluation = evaluationHappy;
                colourInBestChild = colour;
                isHappyInBestChild = true;
            }

            happyVerticesAssignments.makeUnhappy(node->getForgottenVertex());
            int evaluationUnhappy{rankingChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
            if (evaluationUnhappy > evaluation)
            {
                evaluation = evaluationUnhappy;
                colourInBestChild = colour;
                isHappyInBestChild = false;
            }
        }

        if (evaluation > Solvers::ExactTreeDecompositionRankingMHV::NEGATIVE_INFINITY)
        {
            colourAssignments.assignColour(node->getForgottenVertex(), colourInBestChild);
            if (isHappyInBestChild)
                happyVerticesAssignments.makeHappy(node->getForgottenVertex());
            else
                happyVerticesAssignments.makeUnhappy(node->getForgottenVertex());
            std::shared_ptr<DataStructures::ColourAssignment> fullColouringChild = rankingChild.getFullColouring(colourAssignments, happyVerticesAssignments);

            // Remove the colour of the forgotten node
            colourAssignments.removeColour(node->getForgottenVertex());
            happyVerticesAssignments.makeUnhappy(node->getForgottenVertex());

            ranking.addSolution(evaluation, colourAssignments, happyVerticesAssignments, {fullColouringChild});
        }
    }
    return ranking;
}

Solvers::ExactTreeDecompositionRankingMHV MaximumHappyVertices::ExactTreeDecompositionMHV::handleJoinNode(
        std::shared_ptr<DataStructures::JoinNode>& node,
        const Solvers::ExactTreeDecompositionRankingMHV& rankingLeftChild,
        const Solvers::ExactTreeDecompositionRankingMHV& rankingRightChild) const
{
    // Gather all vertices that should be coloured, that is the vertices in S and the vertices in the bag
    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

    // Iterate over all the solutions
    Solvers::ExactTreeDecompositionRankingMHV ranking{};
    ExactTreeDecompositionMHVSolutionIterator iterator{verticesToConsider, graph};

    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);
    for (DataStructures::VertexType vertex : S)
        verticesToConsider.insert(vertex);

    while (iterator.next())
    {
        DataStructures::ColourAssignment colourAssignments{iterator.getColourAssignments()};
        DataStructures::HappyVerticesAssignments happyVerticesAssignments{iterator.getHappyVerticesAssignments()};

        int evaluationLeftChild{rankingLeftChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
        if (evaluationLeftChild == Solvers::ExactTreeDecompositionRankingMHV::NEGATIVE_INFINITY)
            continue;

        int evaluationRightChild{rankingRightChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
        if (evaluationRightChild == Solvers::ExactTreeDecompositionRankingMHV::NEGATIVE_INFINITY)
            continue;

        int nbVerticesCountedDouble{0};
        for (DataStructures::VertexType vertex : verticesToConsider)
        {
            if (happyVerticesAssignments.isHappy(vertex))
                nbVerticesCountedDouble++;
        }

        std::shared_ptr<DataStructures::ColourAssignment> fullColouringLeftChild = rankingLeftChild.getFullColouring(colourAssignments, happyVerticesAssignments);
        std::shared_ptr<DataStructures::ColourAssignment> fullColouringRightChild = rankingRightChild.getFullColouring(colourAssignments, happyVerticesAssignments);

        ranking.addSolution(
            evaluationLeftChild + evaluationRightChild - nbVerticesCountedDouble,
            colourAssignments,
            happyVerticesAssignments,
            {fullColouringLeftChild, fullColouringRightChild}
        );
    }
    return ranking;
}