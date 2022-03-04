//
// Created by louis on 04/02/2022.
//

#include "ExactTreeDecompositionMHV.h"
#include "ExactTreeDecompositionMHVSolutionIterator.h"

#include <algorithm>
#include <cmath>
#include <vector>


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

Solvers::ExactTreeDecompositionRankingMHV MaximumHappyVertices::ExactTreeDecompositionMHV::handleLeafNode(
        DataStructures::LeafNode* node) const
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

Solvers::ExactTreeDecompositionRankingMHV MaximumHappyVertices::ExactTreeDecompositionMHV::handleIntroduceNode(
        DataStructures::IntroduceNode* node,
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
        if (evaluationChild == Solvers::ExactTreeDecompositionRankingMHV::NEGATIVE_INFINITY)
            continue;

//        // Set the colour assignment as the best child colouring and search the concrete child colouring in the child ranking
//        const DataStructures::ColourAssignments& concreteChildColouring = rankingChild.getConcreteAssignment(colourAssignmentsChild, happyVerticesAssignments);
//        for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
//        {
//            colourAssignments.assignColour(vertex, concreteChildColouring.getColour(vertex));
//        }

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

Solvers::ExactTreeDecompositionRankingMHV MaximumHappyVertices::ExactTreeDecompositionMHV::handleForgetNode(
        DataStructures::ForgetNode* node,
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
        DataStructures::ColourAssignments colourAssignments{iterator.getColourAssignments()};
        DataStructures::HappyVerticesAssignments happyVerticesAssignments{iterator.getHappyVerticesAssignments()};
        int evaluation{Solvers::ExactTreeDecompositionRankingMHV::NEGATIVE_INFINITY};
        DataStructures::ColourType colourInBestChild{0};
        for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
        {
            colourAssignments.assignColour(node->getForgottenVertex(), colour);

            happyVerticesAssignments.makeHappy(node->getForgottenVertex());
            int evaluationHappy{rankingChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
            if (evaluationHappy > evaluation)
            {
                evaluation = evaluationHappy;
                colourInBestChild = colour;
            }

            happyVerticesAssignments.makeUnhappy(node->getForgottenVertex());
            int evaluationUnhappy{rankingChild.getEvaluation(colourAssignments, happyVerticesAssignments)};
            if (evaluationUnhappy > evaluation)
            {
                evaluation = evaluationUnhappy;
                colourInBestChild = colour;
            }
        }

//        // Set the colour assignment as the best child colouring and search the concrete child colouring in the child ranking
//        colourAssignments.assignColour(node->getForgottenVertex(), colourInBestChild);
//        const DataStructures::ColourAssignments& concreteChildColouring = rankingChild.getConcreteAssignment(colourAssignments, happyVerticesAssignments);
//        for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
//        {
//            colourAssignments.assignColour(vertex, concreteChildColouring.getColour(vertex));
//        }

        colourAssignments.removeColour(node->getForgottenVertex());
        happyVerticesAssignments.makeUnhappy(node->getForgottenVertex());
        if (evaluation > Solvers::ExactTreeDecompositionRankingMHV::NEGATIVE_INFINITY)
        {
            ranking.addSolution(evaluation, colourAssignments, happyVerticesAssignments);
        }
    }
    return ranking;
}

Solvers::ExactTreeDecompositionRankingMHV MaximumHappyVertices::ExactTreeDecompositionMHV::handleJoinNode(
        DataStructures::JoinNode* node,
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
    while (iterator.next())
    {
        DataStructures::ColourAssignments colourAssignments{iterator.getColourAssignments()};
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

//        const DataStructures::ColourAssignments& concreteLeftChildColouring = rankingLeftChild.getConcreteAssignment(colourAssignments, happyVerticesAssignments);
//        const DataStructures::ColourAssignments& concreteRightChildColouring = rankingLeftChild.getConcreteAssignment(colourAssignments, happyVerticesAssignments);
//        for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
//        {
//            colourAssignments.assignColour(vertex, concreteLeftChildColouring.getColour(vertex));
//            colourAssignments.assignColour(vertex, concreteRightChildColouring.getColour(vertex));
//        }

        ranking.addSolution(
            evaluationLeftChild + evaluationRightChild - nbVerticesCountedDouble,
            colourAssignments,
            happyVerticesAssignments
        );
    }
    return ranking;
}