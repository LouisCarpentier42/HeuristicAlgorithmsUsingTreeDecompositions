//
// Created by louis on 17/03/2022.
//

#include <algorithm>
#include "HeuristicMHVSolverV2.h"
#include "../DataStructures/Evaluator/BasicMHVEvaluator.h"


SolverV2::HeuristicMHVSolverV2::HeuristicMHVSolverV2(int nbSolutionsToKeep) : nbSolutionsToKeep(nbSolutionsToKeep) {}

void SolverV2::HeuristicMHVSolverV2::solve(
        std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition) const
{
    // Create S
    std::set<DataStructures::VertexType> S{};
    std::vector<bool> coloursUsed(graph->getNbColours()+1, false);
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (graph->isPrecoloured(vertex) && !coloursUsed[graph->getColour(vertex)])
        {
            coloursUsed[graph->getColour(vertex)] = true;
            S.insert(vertex);
        }
    }

    HeuristicSolverRankingV2 ranking = solveAtNode(treeDecomposition->getRoot(), graph, S);
//    std::cout << "FINAL RANKING: \n" << ranking << "\n";

    if (ranking.size() > 0)
    {
        HeuristicSolverRankingV2::Entry bestEntry = ranking.getBestEntry();

        // Colour graph
        for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        {
            if (!graph->isPrecoloured(vertex))
                graph->setColour(vertex, std::get<0>(bestEntry).getColour(vertex));
        }
    }
    else
    {
        std::cout << "No viable solution found\n";
    }
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::solveAtNode(
        const std::shared_ptr<DataStructures::NiceNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph,
        const std::set<DataStructures::VertexType>& S) const
{
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
            return handleLeafNode(std::dynamic_pointer_cast<DataStructures::LeafNode>(node), graph, S);
        case DataStructures::NodeType::IntroduceNode:
            return handleIntroduceNode(std::dynamic_pointer_cast<DataStructures::IntroduceNode>(node), graph, S);
        case DataStructures::NodeType::ForgetNode:
            return handleForgetNode(std::dynamic_pointer_cast<DataStructures::ForgetNode>(node), graph, S);
        case DataStructures::NodeType::JoinNode:
            return handleJoinNode(std::dynamic_pointer_cast<DataStructures::JoinNode>(node), graph, S);
    }

//    switch(node->getNodeType())
//    {
//        case DataStructures::NodeType::LeafNode:
//        {
//            auto ranking = handleLeafNode(std::dynamic_pointer_cast<DataStructures::LeafNode>(node), graph, S);
//
//            std::set<DataStructures::VertexType> verticesToConsider{S};
//            for (DataStructures::VertexType vertex : node->getBagContent())
//                verticesToConsider.insert(vertex);
//            for (const HeuristicSolverRankingV2::Entry& entry : ranking)
//            {
//                std::set<HeuristicSolverRankingV2::Entry> matches;
//                for (const HeuristicSolverRankingV2::Entry& other : ranking)
//                {
//                    bool isMatch{true};
//                    for (auto v : verticesToConsider)
//                    {
//                        if (std::get<0>(entry).getColour(v) == std::get<0>(other).getColour(v) && std::get<1>(entry).getHappiness(v) == std::get<1>(other).getHappiness(v))
//                        {
//
//                        }
//                        else
//                        {
//                            isMatch = false;
//                            break;
//                        }
//                    }
//
//                    if (isMatch)
//                    {
//                        matches.insert(other);
//                    }
//                }
//
//                if (matches.size() > 1)
//                {
//                    std::cout << "Duplicates in Leaf node " << node->getId() << ":\n";
//                    std::cout << "Vertices to consider: ";
//                    for (auto v : verticesToConsider) std::cout << v << ", ";
//                    std::cout << "\n";
//                    std::cout << "l: " << entry << "\n";
//                    for (auto& match : matches) std::cout << match << "\n";
//                    std::cout << "\n";
//                }
//            }
//
//            return ranking;
//        }
//        case DataStructures::NodeType::IntroduceNode:
//        {
//            auto ranking = handleIntroduceNode(std::dynamic_pointer_cast<DataStructures::IntroduceNode>(node), graph, S);
//
//            std::set<DataStructures::VertexType> verticesToConsider{S};
//            for (DataStructures::VertexType vertex : node->getBagContent())
//                verticesToConsider.insert(vertex);
//            for (const HeuristicSolverRankingV2::Entry& entry : ranking)
//            {
//                std::set<HeuristicSolverRankingV2::Entry> matches;
//                for (const HeuristicSolverRankingV2::Entry& other : ranking)
//                {
//                    bool isMatch{true};
//                    for (auto v : verticesToConsider)
//                    {
//                        if (std::get<0>(entry).getColour(v) == std::get<0>(other).getColour(v) && std::get<1>(entry).getHappiness(v) == std::get<1>(other).getHappiness(v))
//                        {
//
//                        }
//                        else
//                        {
//                            isMatch = false;
//                            break;
//                        }
//                    }
//
//                    if (isMatch)
//                    {
//                        matches.insert(other);
//                    }
//                }
//
//                if (matches.size() > 1)
//                {
//                    std::cout << "Duplicates in Introduce node " << node->getId() << ":\n";
//                    std::cout << "Vertices to consider: ";
//                    for (auto v : verticesToConsider) std::cout << v << ", ";
//                    std::cout << "\n";
//                    std::cout << "l: " << entry << "\n";
//                    for (auto& match : matches) std::cout << match << "\n";
//                    std::cout << "\n";
//                }
//            }
//
//            return ranking;
//        }
//        case DataStructures::NodeType::ForgetNode:
//        {
//            auto ranking = handleForgetNode(std::dynamic_pointer_cast<DataStructures::ForgetNode>(node), graph, S);
//
//            std::set<DataStructures::VertexType> verticesToConsider{S};
//            for (DataStructures::VertexType vertex : node->getBagContent())
//                verticesToConsider.insert(vertex);
//            for (const HeuristicSolverRankingV2::Entry& entry : ranking)
//            {
//                std::set<HeuristicSolverRankingV2::Entry> matches;
//                for (const HeuristicSolverRankingV2::Entry& other : ranking)
//                {
//                    bool isMatch{true};
//                    for (auto v : verticesToConsider)
//                    {
//                        if (std::get<0>(entry).getColour(v) == std::get<0>(other).getColour(v) && std::get<1>(entry).getHappiness(v) == std::get<1>(other).getHappiness(v))
//                        {
//
//                        }
//                        else
//                        {
//                            isMatch = false;
//                            break;
//                        }
//                    }
//
//                    if (isMatch)
//                    {
//                        matches.insert(other);
//                    }
//                }
//
//                if (matches.size() > 1)
//                {
//                    std::cout << "Duplicates in Forget node " << node->getId() << ":\n";
//                    std::cout << "Vertices to consider: ";
//                    for (auto v : verticesToConsider) std::cout << v << ", ";
//                    std::cout << "\n";
//                    std::cout << "l: " << entry << "\n";
//                    for (auto& match : matches) std::cout << match << "\n";
//                    std::cout << "\n";
//                }
//            }
//
//            return ranking;
//        }
//        case DataStructures::NodeType::JoinNode:
//        {
//            auto ranking = handleJoinNode(std::dynamic_pointer_cast<DataStructures::JoinNode>(node), graph, S);
//
//            std::set<DataStructures::VertexType> verticesToConsider{S};
//            for (DataStructures::VertexType vertex : node->getBagContent())
//                verticesToConsider.insert(vertex);
//            for (const HeuristicSolverRankingV2::Entry& entry : ranking)
//            {
//                std::set<HeuristicSolverRankingV2::Entry> matches;
//                for (const HeuristicSolverRankingV2::Entry& other : ranking)
//                {
//                    bool isMatch{true};
//                    for (auto v : verticesToConsider)
//                    {
//                        if (std::get<0>(entry).getColour(v) == std::get<0>(other).getColour(v) && std::get<1>(entry).getHappiness(v) == std::get<1>(other).getHappiness(v))
//                        {
//
//                        }
//                        else
//                        {
//                            isMatch = false;
//                            break;
//                        }
//                    }
//
//                    if (isMatch)
//                    {
//                        matches.insert(other);
//                    }
//                }
//
//                if (matches.size() > 1)
//                {
//                    std::cout << "Duplicates in Join node " << node->getId() << ":\n";
//                    std::cout << "Vertices to consider: ";
//                    for (auto v : verticesToConsider) std::cout << v << ", ";
//                    std::cout << "\n";
//                    std::cout << "l: " << entry << "\n";
//                    for (auto& match : matches) std::cout << match << "\n";
//                    std::cout << "\n";
//                }
//            }
//
//            return ranking;
//        }
//    }
}

int SolverV2::HeuristicMHVSolverV2::getEvaluation(const HappyVertexAssignmentV2& happyVertexAssignment) const
{
    return weightHappyVertices * happyVertexAssignment.getCountOf(HappinessValues::happy);
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleLeafNode(
        const std::shared_ptr<DataStructures::LeafNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph,
        const std::set<DataStructures::VertexType>& S) const
{
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};

    HappyVertexAssignmentV2 allVerticesHappy{graph};

    // Find the set of vertices that are happy
    std::set<DataStructures::VertexType> happyVertices{};
    for (DataStructures::VertexType vertex : S)
    {
        bool noneEmptyIntersection = std::any_of(
                graph->getNeighbours(vertex).begin(),
                graph->getNeighbours(vertex).end(),
                [S](DataStructures::VertexType neighbour){return S.find(neighbour) != S.end(); });
        // If the neighbours and S have a none-empty intersection, then one of the neighbours
        // of vertex has a different colour since all the vertices in S have a different colour
        if (!noneEmptyIntersection)
        {
            happyVertices.insert(vertex);
            allVerticesHappy.makeHappy(vertex);
        }
        else
        {
            allVerticesHappy.makeUnhappy(vertex);
        }
    }

    // Add assignment in which all vertices are assigned happy
    ColourAssignmentV2 allHappyColourAssignments{graph};
    for (DataStructures::VertexType vertexInS : S)
        allHappyColourAssignments.setColour(vertexInS, graph->getColour(vertexInS));
    HappyVertexAssignmentV2 allHappyHappyVerticesAssignments{allVerticesHappy};
    ranking.push(allHappyColourAssignments, allHappyHappyVerticesAssignments, getEvaluation(allHappyHappyVerticesAssignments));

    // Variable to know which vertices must be assigned unhappy
    std::set<std::set<DataStructures::VertexType>> unhappyVertexAssignments{};
    unhappyVertexAssignments.insert(std::set<DataStructures::VertexType>{}); // Add empty set (all are happy)

    while (!ranking.hasReachedCapacity() && (*unhappyVertexAssignments.begin()).size() < happyVertices.size())
    {
        std::set<std::set<DataStructures::VertexType>> newUnhappyVertexAssignments{};
        for (const std::set<DataStructures::VertexType>& unhappyVertices : unhappyVertexAssignments)
        {
            for (DataStructures::VertexType vertex : happyVertices)
            {
                if (unhappyVertices.find(vertex) == unhappyVertices.end())
                {
                    // Create new unhappy vertices
                    std::set<DataStructures::VertexType> newUnhappyVertices{unhappyVertices};
                    newUnhappyVertices.insert(vertex);
                    newUnhappyVertexAssignments.insert(newUnhappyVertices);
                }
            }
        }
        unhappyVertexAssignments = newUnhappyVertexAssignments;

        for (const std::set<DataStructures::VertexType>& unhappyVertices : unhappyVertexAssignments)
        {
            // Create the partition of S for the colours
            ColourAssignmentV2 colourAssignments{graph};
            for (DataStructures::VertexType vertexInS : S)
                colourAssignments.setColour(vertexInS, graph->getColour(vertexInS));
            // Create the happy vertex assignment
            HappyVertexAssignmentV2 happyVerticesAssignments{allVerticesHappy};
            for (DataStructures::VertexType unhappyVertex : unhappyVertices)
                happyVerticesAssignments.makeUnhappy(unhappyVertex);
            // Add the assignment to the ranking
            ranking.push(colourAssignments, happyVerticesAssignments, getEvaluation(happyVerticesAssignments));
        }
    }

    return ranking;
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleIntroduceNode(
        const std::shared_ptr<DataStructures::IntroduceNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph,
        const std::set<DataStructures::VertexType>& S) const
{
    HeuristicSolverRankingV2 rankingChild = solveAtNode(node->getChild(), graph, S);

    if (S.find(node->getIntroducedVertex()) != S.end())
    {
        return rankingChild;
    }

    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};

    for (auto& [colourAssignmentChild, happyVerticesAssignmentsChild, evaluationChild] : rankingChild)
    {
//        for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
//        {
//            std::set<DataStructures::ColourType> otherColoursOfNeighbours{};
//            std::set<DataStructures::ColourType> otherColoursOfHappyNeighbours{};
//            for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
//            {
//                if (!colourAssignmentChild.isColoured(neighbour))
//                    continue;
//
//                if (colourAssignmentChild.getColour(neighbour) != colour)
//                {
//                    otherColoursOfNeighbours.insert(colourAssignmentChild.getColour(neighbour));
//                    if (happyVerticesAssignmentsChild.isHappy(neighbour))
//                    {
//                        otherColoursOfHappyNeighbours.insert(colourAssignmentChild.getColour(neighbour));
//                        break;
//                    }
//                }
//            }
//
//            if (!otherColoursOfHappyNeighbours.empty())
//            {
//                continue;
//            }
//            else
//            {
//                if (otherColoursOfNeighbours.empty())
//                {
//                    ColourAssignmentV2 colourAssignment{colourAssignmentChild};
//                    colourAssignment.setColour(node->getIntroducedVertex(), colour);
//                    HappyVertexAssignmentV2 happyVertexAssignment{happyVerticesAssignmentsChild};
//                    happyVertexAssignment.makeHappy(node->getIntroducedVertex());
//
//                    ranking.push(colourAssignment, happyVertexAssignment, getEvaluation(happyVertexAssignment));
//                }
//
//                ColourAssignmentV2 colourAssignment{colourAssignmentChild};
//                colourAssignment.setColour(node->getIntroducedVertex(), colour);
//                HappyVertexAssignmentV2 happyVertexAssignment{happyVerticesAssignmentsChild};
//                happyVertexAssignment.makeUnhappy(node->getIntroducedVertex());
//
//                ranking.push(colourAssignment, happyVertexAssignment, getEvaluation(happyVertexAssignment));
//            }
//
//        }

        // TODO can be optimized by gathering the valid colours for assigning happy and unhappy
        for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
        {
            if (graph->isPrecoloured(node->getIntroducedVertex()) && graph->getColour(node->getIntroducedVertex()) != colour) continue;

            bool allNeighboursSameColour{true};
            bool allHappyNeighboursSameColour{true};
            for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
            {
                if (colourAssignmentChild.isColoured(neighbour) && colourAssignmentChild.getColour(neighbour) != colour)
                {
                    allNeighboursSameColour = false;
                    if (happyVerticesAssignmentsChild.isHappy(neighbour))
                    {
                        allHappyNeighboursSameColour = false;
                        break;
                    }
                }
            }

            if (!allHappyNeighboursSameColour)
            {
                HappyVertexAssignmentV2 newHappyVertexAssignment{happyVerticesAssignmentsChild};
                newHappyVertexAssignment.makeUnhappy(node->getIntroducedVertex());
                for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
                {
                    if (colourAssignmentChild.isColoured(neighbour) &&
                        colourAssignmentChild.getColour(neighbour) != colour &&
                        happyVerticesAssignmentsChild.isHappy(neighbour))
                    {
                        newHappyVertexAssignment.makeUnhappy(neighbour);
                    }
                }

                ColourAssignmentV2 newColourAssignment{colourAssignmentChild};
                newColourAssignment.setColour(node->getIntroducedVertex(), colour);
                ranking.push(newColourAssignment, newHappyVertexAssignment, getEvaluation(newHappyVertexAssignment));
            }
            else
            {
                // Only if all coloured neighbours have the same colour, the vertex can be happy
                if (allNeighboursSameColour)
                {
                    ColourAssignmentV2 colourAssignmentHappy{colourAssignmentChild};
                    colourAssignmentHappy.setColour(node->getIntroducedVertex(), colour);
                    HappyVertexAssignmentV2 happyVerticesAssignmentsHappy{happyVerticesAssignmentsChild};
                    happyVerticesAssignmentsHappy.makeHappy(node->getIntroducedVertex());

                    ranking.push(colourAssignmentHappy, happyVerticesAssignmentsHappy, getEvaluation(happyVerticesAssignmentsHappy));
                }

                // Assigning the introduced vertex unhappy can be done without any axuiliary checks
                ColourAssignmentV2 colourAssignmentUnhappy{colourAssignmentChild};
                colourAssignmentUnhappy.setColour(node->getIntroducedVertex(), colour);
                HappyVertexAssignmentV2 happyVerticesAssignmentsUnhappy{happyVerticesAssignmentsChild};
                happyVerticesAssignmentsUnhappy.makeUnhappy(node->getIntroducedVertex());

                ranking.push(colourAssignmentUnhappy, happyVerticesAssignmentsUnhappy, getEvaluation(happyVerticesAssignmentsUnhappy));
            }
        }
    }

    return ranking;
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleForgetNode(
        const std::shared_ptr<DataStructures::ForgetNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph,
        const std::set<DataStructures::VertexType>& S) const
{
    HeuristicSolverRankingV2 rankingChild = solveAtNode(node->getChild(), graph, S);
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};

    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

    std::set<HeuristicSolverRankingV2::Entry> bestEntries{};

    for (const HeuristicSolverRankingV2::Entry& entry : rankingChild)
    {
        bool shouldAddEntry{true};
        for (HeuristicSolverRankingV2::Entry bestEntry : bestEntries)
        {
            bool bestEntryEqualsEntry{true};
            for (DataStructures::VertexType vertex : verticesToConsider)
            {
                bool sameColour = std::get<0>(bestEntry).getColour(vertex) == std::get<0>(entry).getColour(vertex);
                bool sameHappiness = std::get<1>(bestEntry).getHappiness(vertex) == std::get<1>(entry).getHappiness(vertex);
                if (!(sameColour && sameHappiness))
                {
                    bestEntryEqualsEntry = false;
                    break;
                }
            }
            if (bestEntryEqualsEntry)
            {
                shouldAddEntry = false;
                break;
            }
        }

        if (!shouldAddEntry) continue;

        HeuristicSolverRankingV2::Entry bestEntry = entry;
        for (const HeuristicSolverRankingV2::Entry& other : rankingChild)
        {
            bool otherEqualsEntry{true};
            for (DataStructures::VertexType vertex : verticesToConsider)
            {
                bool sameColour = std::get<0>(entry).getColour(vertex) == std::get<0>(other).getColour(vertex);
                bool sameHappiness = std::get<1>(entry).getHappiness(vertex) == std::get<1>(other).getHappiness(vertex);
                if (!(sameColour && sameHappiness))
                {
                    otherEqualsEntry = false;
                    break;
                }
            }

            if (otherEqualsEntry && std::get<2>(other) > std::get<2>(bestEntry))
            {
                bestEntry = other;
            }
        }
        bestEntries.insert(bestEntry);
        ranking.push(std::get<0>(bestEntry), std::get<1>(bestEntry), std::get<2>(bestEntry)); // TODO add method in ranking to push entry as a whole (+ maybe call then this method from the already existing one)
    }

    return ranking;
}



SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleJoinNode(
        const std::shared_ptr<DataStructures::JoinNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph,
        const std::set<DataStructures::VertexType>& S) const
{
    HeuristicSolverRankingV2 rankingLeftChild = solveAtNode(node->getLeftChild(), graph, S);
    HeuristicSolverRankingV2 rankingRightChild = solveAtNode(node->getRightChild(), graph, S);
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};

    // Gather all vertices that should be coloured, that is the vertices in S and the vertices in the bag
    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

    for (auto& [colourAssignmentLeft, happyVerticesAssignmentsLeft, evaluationLeft] : rankingLeftChild) // TODO maybe change to entry
    {
        int bestNbMistakes = graph->getNbVertices() + 1;
        ColourAssignmentV2 bestColouringRight{graph};
        HappyVertexAssignmentV2 bestHappinessRight{graph};
        int bestEvaluationRight;

        std::set<HeuristicSolverRankingV2::Entry> matches;
        for (auto& [colourAssignmentRight, happyVerticesAssignmentsRight, evaluationRight] : rankingRightChild)
        {
            int nbMistakes{0};
            for (DataStructures::VertexType vertex : verticesToConsider)
            {
                bool sameColour = colourAssignmentLeft.getColour(vertex) == colourAssignmentRight.getColour(vertex);
                bool sameHappiness = happyVerticesAssignmentsLeft.isHappy(vertex) == happyVerticesAssignmentsRight.isHappy(vertex);
                if (!(sameColour && sameHappiness))
                {
                    nbMistakes++;
                }
            }

            if (nbMistakes == 0)
            {
                bestNbMistakes = 0;
                matches.insert(std::make_tuple(colourAssignmentRight, happyVerticesAssignmentsRight, evaluationRight));
                HappyVertexAssignmentV2 mergedHappiness{graph};
                for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
                {
                    if (happyVerticesAssignmentsLeft.isHappy(vertex) || happyVerticesAssignmentsRight.isHappy(vertex))
                        mergedHappiness.makeHappy(vertex);
                    else
                        mergedHappiness.makeUnhappy(vertex);
                }
                ranking.push(
                        ColourAssignmentV2{colourAssignmentLeft, colourAssignmentRight},
                        mergedHappiness,
                        getEvaluation(mergedHappiness));

                break;
            }

            if (nbMistakes < bestNbMistakes)
            {
                bestNbMistakes = nbMistakes;
                bestColouringRight = colourAssignmentRight;
                bestHappinessRight = happyVerticesAssignmentsRight;
                bestEvaluationRight = evaluationRight;
            }
        }

        if (bestNbMistakes > 0)
        {
            mergeAndAddDifferingEntries(
                    ranking, node, graph,
                    colourAssignmentLeft, happyVerticesAssignmentsLeft, evaluationLeft,
                    bestColouringRight, bestHappinessRight, bestEvaluationRight);
            mergeAndAddDifferingEntries(
                    ranking, node, graph,
                    bestColouringRight, bestHappinessRight, bestEvaluationRight,
                    colourAssignmentLeft, happyVerticesAssignmentsLeft, evaluationLeft);
        }
    }

    return ranking;
}

void SolverV2::HeuristicMHVSolverV2::mergeAndAddDifferingEntries(
        SolverV2::HeuristicSolverRankingV2 &ranking,
        const std::shared_ptr<DataStructures::JoinNode> &node,
        const std::shared_ptr<DataStructures::Graph> &graph,
        const ColourAssignmentV2 &primaryColouring,
        const SolverV2::HappyVertexAssignmentV2 &primaryHappiness,
        int evaluationPrimary,
        const ColourAssignmentV2 &secondaryColouring,
        const SolverV2::HappyVertexAssignmentV2 &secondaryHappiness,
        int evaluationSecondary) const
{
    ColourAssignmentV2 mergedColouring{primaryColouring, secondaryColouring};
    SolverV2::HappyVertexAssignmentV2 mergedHappiness{graph};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (primaryColouring.isColoured(vertex) && secondaryColouring.isColoured(vertex))
        {
            if (primaryHappiness.isHappy(vertex))
            {
                bool anyNeighbourColouredDifferently{false};
                for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
                {
                    if (mergedColouring.isColoured(neighbour) && mergedColouring.getColour(neighbour) != mergedColouring.getColour(vertex))
                    {
                        // Was happy but actually not
                        anyNeighbourColouredDifferently = true;
                        break;
                    }
                }

                if (!anyNeighbourColouredDifferently)
                {
                    mergedHappiness.makeHappy(vertex);
                }
                else
                {
                    mergedHappiness.makeUnhappy(vertex);
                }
            }
            else
            {
                mergedHappiness.makeUnhappy(vertex);
            }
        }
        else if (primaryColouring.isColoured(vertex) && !secondaryColouring.isColoured(vertex))
        {
            if (primaryHappiness.isHappy(vertex))
            {
                mergedHappiness.makeHappy(vertex);
            }
            else
            {
                mergedHappiness.makeUnhappy(vertex);
            }
        }
        else if (!primaryColouring.isColoured(vertex) && secondaryColouring.isColoured(vertex))
        {
            if (secondaryHappiness.isHappy(vertex))
            {
                bool anyNeighbourColouredDifferently{false};
                for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
                {
                    if (mergedColouring.isColoured(neighbour) && mergedColouring.getColour(neighbour) != mergedColouring.getColour(vertex))
                    {
                        // Was happy but actually not
                        anyNeighbourColouredDifferently = true;
                        break;
                    }
                }

                if (!anyNeighbourColouredDifferently)
                {
                    mergedHappiness.makeHappy(vertex);
                }
                else
                {
                    mergedHappiness.makeUnhappy(vertex);
                }
            }
            else
            {
                mergedHappiness.makeUnhappy(vertex);
            }
        }
    }

    // Add colouring
    ranking.push(mergedColouring, mergedHappiness, getEvaluation(mergedHappiness));
}


