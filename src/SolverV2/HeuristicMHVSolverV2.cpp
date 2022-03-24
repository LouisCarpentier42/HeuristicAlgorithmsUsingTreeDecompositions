//
// Created by louis on 17/03/2022.
//

#include <algorithm>
#include "HeuristicMHVSolverV2.h"
#include "../DataStructures/Evaluator/BasicMHVEvaluator.h"

SolverV2::HeuristicMHVSolverV2::HeuristicMHVSolverV2(
        int nbSolutionsToKeep, int weightHappyVertices, int weightPotentialHappyVertices, int weightUnhappyVertices)
    : nbSolutionsToKeep(nbSolutionsToKeep),
      weightHappyVertices{weightHappyVertices},
      weightPotentialHappyVertices{weightPotentialHappyVertices},
      weightUnhappyVertices{weightUnhappyVertices}
{ }

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
}

int SolverV2::HeuristicMHVSolverV2::getEvaluation(const HappyVertexAssignmentV2& happyVertexAssignment) const
{
    return weightHappyVertices * happyVertexAssignment.getCountOf(HappinessValue::happy) +
           weightPotentialHappyVertices * happyVertexAssignment.getCountOf(HappinessValue::potentiallyHappy) +
           weightUnhappyVertices * happyVertexAssignment.getCountOf(HappinessValue::unhappy);
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleLeafNode(
        const std::shared_ptr<DataStructures::LeafNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph,
        const std::set<DataStructures::VertexType>& S) const
{
    // Create an empty ranking
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};

    // Initialise the colouring and find which vertices in S can be happy
    ColourAssignmentV2 colourAssignment{graph};
    HappyVertexAssignmentV2 allPossibleHappyVerticesHappy{graph};
    std::set<DataStructures::VertexType> happyVertices{};
    for (DataStructures::VertexType vertex : S)
    {
        // Set the colour of the vertex
        colourAssignment.setColour(vertex, graph->getColour(vertex));
        bool noneEmptyIntersection = std::any_of(
                graph->getNeighbours(vertex).begin(),
                graph->getNeighbours(vertex).end(),
                [S](DataStructures::VertexType neighbour){return S.find(neighbour) != S.end(); });
        // If the neighbours and S have a none-empty intersection, then one of the neighbours
        // of vertex has a different colour since all the vertices in S have a different colour
        if (!noneEmptyIntersection)
        {
            happyVertices.insert(vertex);
            allPossibleHappyVerticesHappy.setHappiness(vertex, HappinessValue::happy);
        }
        else
        {
            allPossibleHappyVerticesHappy.setHappiness(vertex, HappinessValue::unhappy);
        }

        // Check if the neighbours could be potentially happy
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            // Skip if type is already known
            if (allPossibleHappyVerticesHappy.getHappiness(neighbour) != HappinessValue::unknown) continue;

            // Check if the vertex has another neighbour in S, thus if it has two neighbours of a different colour
            bool hasOtherNeighbourInS = std::any_of(
                    graph->getNeighbours(neighbour).begin(),
                    graph->getNeighbours(neighbour).end(),
                    [S, vertex](auto other) { return other != vertex && S.find(other) != S.end(); }
                );

            // If the vertex has a neighbour in a different colour, then it will always be unhappy, otherwise it could
            // potentially become happy
            if (hasOtherNeighbourInS)
            {
                allPossibleHappyVerticesHappy.setHappiness(neighbour, HappinessValue::unhappy);
            }
            else
            {
                allPossibleHappyVerticesHappy.setHappiness(neighbour, HappinessValue::potentiallyHappy);
            }
        }
    }

    // Add assignment in which all vertices are assigned happy
    ranking.push(colourAssignment, allPossibleHappyVerticesHappy, getEvaluation(allPossibleHappyVerticesHappy));

    // Variable to know which vertices to make unhappy
    std::vector<std::set<DataStructures::VertexType>> unhappyVertexAssignments{};
    unhappyVertexAssignments.emplace_back(); // Add empty set (all are happy)

    // Make more vertices unhappy until the ranking reaches its capacity or if there can't be made any more vertices unhappy
    // At each iteration will one more vertex that could be happy set to unhappy. By doing this we promote to have more
    // vertices happy than unhappy
    while (!ranking.hasReachedCapacity() && (*unhappyVertexAssignments.begin()).size() < happyVertices.size())
    {
        // The new sets of vertices that should be made unhappy. These sets are created by taking every possible set of
        // the previous iteration and then add each possible vertex to it (if it's not already in the set).
        std::vector<std::set<DataStructures::VertexType>> newUnhappyVertexAssignments{};
        for (const std::set<DataStructures::VertexType>& unhappyVertices : unhappyVertexAssignments)
        {
            for (DataStructures::VertexType vertex : happyVertices)
            {
                if (unhappyVertices.find(vertex) == unhappyVertices.end())
                {
                    // Create new unhappy vertices
                    std::set<DataStructures::VertexType> newUnhappyVertices{unhappyVertices};
                    newUnhappyVertices.insert(vertex);
                    newUnhappyVertexAssignments.push_back(newUnhappyVertices);
                }
            }
        }

        // Replace the exising sets of vertices to the new sets
        unhappyVertexAssignments = newUnhappyVertexAssignments;

        // Add all the entries to the ranking, in which some vertices are made unhappy
        for (const std::set<DataStructures::VertexType>& unhappyVertices : unhappyVertexAssignments)
        {
            // Create the happy vertex assignment and make the correct vertices unhappy
            HappyVertexAssignmentV2 happyVerticesAssignments{allPossibleHappyVerticesHappy};
            for (DataStructures::VertexType unhappyVertex : unhappyVertices)
                happyVerticesAssignments.setHappiness(unhappyVertex, HappinessValue::unhappy);
            // Add the assignment to the ranking
            ranking.push(colourAssignment, happyVerticesAssignments, getEvaluation(happyVerticesAssignments));
        }
    }

    // Return the computed ranking
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

    for (const HeuristicSolverRankingV2::Entry& entry : rankingChild)
    {

        for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
        {
            if (graph->isPrecoloured(node->getIntroducedVertex()) && graph->getColour(node->getIntroducedVertex()) != colour) continue;

            HappyVertexAssignmentV2 happyVertexAssignmentWithNeighbours{std::get<1>(entry)};

            bool allNeighboursSameColour{true};
            bool allHappyNeighboursSameColour{true};
            for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
            {
                if (std::get<0>(entry).isColoured(neighbour))
                {
                    if (std::get<0>(entry).isColoured(neighbour) && std::get<0>(entry).getColour(neighbour) != colour)
                    {
                        allNeighboursSameColour = false;
                        if (std::get<1>(entry).getHappiness(neighbour) == HappinessValue::happy)
                        {
                            allHappyNeighboursSameColour = false;
                        }
                    }
                }
                else
                {
                    if (happyVertexAssignmentWithNeighbours.getHappiness(neighbour) == HappinessValue::unhappy)
                    {
                        // If the neighbour is already unhappy then it will remain unhappy
                    }
                    else
                    {
                        // If any of the neighbour's neighbours is coloured differently than the colour for the introduced node,
                        // then the neighbour will be unhappy and else potentially happy
                        if (std::any_of(
                                graph->getNeighbours(neighbour).begin(),
                                graph->getNeighbours(neighbour).end(),
                                [entry, colour](DataStructures::VertexType neighbourOfNeighbour)
                                {
                                    return std::get<0>(entry).isColoured(neighbourOfNeighbour) && std::get<0>(entry).getColour(neighbourOfNeighbour) != colour;
                                }
                            ))
                        {
                            happyVertexAssignmentWithNeighbours.setHappiness(neighbour, HappinessValue::unhappy);
                        }
                        else
                        {
                            happyVertexAssignmentWithNeighbours.setHappiness(neighbour, HappinessValue::potentiallyHappy);
                        }
                    }
                }
            }

            if (!allHappyNeighboursSameColour)
            {
                // TODO check if this is the best option for no valid colouring (maybe use a backup or something?)
                ColourAssignmentV2 colourAssignment{std::get<0>(entry)};
                colourAssignment.setColour(node->getIntroducedVertex(), colour);
                HappyVertexAssignmentV2 happyVertexAssignment{happyVertexAssignmentWithNeighbours};
                happyVertexAssignment.setHappiness(node->getIntroducedVertex(), HappinessValue::unhappy);
                for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
                {
                    if (std::get<0>(entry).isColoured(neighbour) &&
                        std::get<0>(entry).getColour(neighbour) != colour &&
                        std::get<1>(entry).getHappiness(neighbour) == HappinessValue::happy)
                    {
                        happyVertexAssignment.setHappiness(neighbour, HappinessValue::unhappy);
                    }
                }

                ranking.push(colourAssignment, happyVertexAssignment, getEvaluation(happyVertexAssignment));
            }
            else
            {
                // Only if all coloured neighbours have the same colour, the vertex can be happy
                if (allNeighboursSameColour)
                {
                    ColourAssignmentV2 colourAssignment{std::get<0>(entry)};
                    colourAssignment.setColour(node->getIntroducedVertex(), colour);
                    HappyVertexAssignmentV2 happyVertexAssignment{happyVertexAssignmentWithNeighbours};
                    happyVertexAssignment.setHappiness(node->getIntroducedVertex(), HappinessValue::happy);

                    ranking.push(colourAssignment, happyVertexAssignment, getEvaluation(happyVertexAssignment));
                }

                // Assigning the introduced vertex unhappy can be done without any auxiliary checks
                ColourAssignmentV2 colourAssignment{std::get<0>(entry)};
                colourAssignment.setColour(node->getIntroducedVertex(), colour);
                HappyVertexAssignmentV2 happyVertexAssignment{happyVertexAssignmentWithNeighbours};
                happyVertexAssignment.setHappiness(node->getIntroducedVertex(), HappinessValue::unhappy);

                ranking.push(colourAssignment, happyVertexAssignment, getEvaluation(happyVertexAssignment));
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
    // Compute the ranking for the child node
    HeuristicSolverRankingV2 rankingChild = solveAtNode(node->getChild(), graph, S);

    // Compute the vertices that are important, that is the vertices in the bag and in S
    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

    // A set to keep track of the unique entries to add, that is the entries with unique colour and happiness for
    // the vertices to consider
    auto comparator =
            [verticesToConsider]
            (const HeuristicSolverRankingV2::Entry& e1, const HeuristicSolverRankingV2::Entry& e2)
            {
                for (DataStructures::VertexType vertex : verticesToConsider)
                {
                    if (std::get<0>(e1).getColour(vertex) != std::get<0>(e2).getColour(vertex))
                        return std::get<0>(e1).getColour(vertex) < std::get<0>(e2).getColour(vertex);
                    else if (std::get<1>(e1).getHappiness(vertex) != std::get<1>(e2).getHappiness(vertex))
                        return std::get<1>(e1).getHappiness(vertex) < std::get<1>(e2).getHappiness(vertex);
                }
                return false;
            };
    std::set<HeuristicSolverRankingV2::Entry, decltype(comparator)> entriesToAdd(comparator);

    // Iterate over the entries of the child and check if it should be added to the new ranking
    for (const HeuristicSolverRankingV2::Entry& entry : rankingChild)
    {
        // Find if the entry is already present in the set
        auto it = entriesToAdd.find(entry);

        if (it == entriesToAdd.end())
        {
            // If the entry is not yet present in the set, then it must be inserted
            entriesToAdd.insert(entry);
        }
        else
        {
            // If the entry is already present in the set, then it should replace the existing entry if it
            // has a higher evaluation
            if (std::get<2>(*it) < std::get<2>(entry))
            {
                entriesToAdd.erase(it);
                entriesToAdd.insert(entry);
            }
        }
    }

    // Create a new ranking for the entries that must be added
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};
    for (const HeuristicSolverRankingV2::Entry& entry : entriesToAdd)
        ranking.push(entry);

    // Return the newly created ranking
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

//    HeuristicSolverRankingV2 biggestRanking = std::max(rankingLeftChild, rankingRightChild, [](auto& r1, auto& r2){return r1.size() < r2.size();});
//    HeuristicSolverRankingV2 smallestRanking = std::min(rankingLeftChild, rankingRightChild, [](auto& r1, auto& r2){return r1.size() < r2.size();});

    // TODO first iterate over child with fewest entries in ranking
    for (const HeuristicSolverRankingV2::Entry& entryLeft : rankingLeftChild)
    {
        int bestNbMistakes = graph->getNbVertices() + 1;
        HeuristicSolverRankingV2::Entry bestEntry = *rankingRightChild.begin();

        for (const HeuristicSolverRankingV2::Entry& entryRight : rankingRightChild)
        {
            int nbMistakes{0};
            for (DataStructures::VertexType vertex : verticesToConsider)
            {
                if (std::get<0>(entryLeft).getColour(vertex) != std::get<0>(entryRight).getColour(vertex) ||
                    std::get<1>(entryLeft).getHappiness(vertex) != std::get<1>(entryRight).getHappiness(vertex))
                {
                    nbMistakes++;
                }
            }

            if (nbMistakes == 0)
            {
                HappyVertexAssignmentV2 mergedHappiness{std::get<1>(entryLeft)};
                for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
                {
                    if (!std::get<0>(entryLeft).isColoured(vertex) && std::get<0>(entryRight).isColoured(vertex))
                    {
                        mergedHappiness.setHappiness(vertex, std::get<1>(entryRight).getHappiness(vertex));
                    }
                }

                ranking.push(
                        ColourAssignmentV2{std::get<0>(entryLeft), std::get<0>(entryRight)},
                        mergedHappiness,
                        getEvaluation(mergedHappiness));
                bestNbMistakes = 0;
                break;
            }

            if (nbMistakes < bestNbMistakes)
            {
                bestNbMistakes = nbMistakes;
                bestEntry = entryRight;
            }
        }

        if (bestNbMistakes > 0)
        {
            mergeAndAddDifferingEntries(
                    ranking, node, graph,
                    entryLeft, bestEntry);
            mergeAndAddDifferingEntries(
                    ranking, node, graph,
                    bestEntry, entryLeft);
        }
    }

    return ranking;
}

void SolverV2::HeuristicMHVSolverV2::mergeAndAddDifferingEntries(
        SolverV2::HeuristicSolverRankingV2& ranking,
        const std::shared_ptr<DataStructures::JoinNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph,
        const SolverV2::HeuristicSolverRankingV2::Entry& primaryEntry,
        const SolverV2::HeuristicSolverRankingV2::Entry& secondaryEntry) const
{
    ColourAssignmentV2 mergedColouring{std::get<0>(primaryEntry), std::get<0>(secondaryEntry)};
    SolverV2::HappyVertexAssignmentV2 mergedHappiness{std::get<1>(primaryEntry)};
    // TODO check happy/unhappy/potential
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (std::get<0>(primaryEntry).isColoured(vertex) && std::get<0>(secondaryEntry).isColoured(vertex))
        {
            if (std::get<1>(primaryEntry).getHappiness(vertex) == HappinessValue::happy)
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

                if (anyNeighbourColouredDifferently)
                {
                    mergedHappiness.setHappiness(vertex, HappinessValue::unhappy);
                }
            }
        }
        else if (!std::get<0>(primaryEntry).isColoured(vertex) && std::get<0>(secondaryEntry).isColoured(vertex))
        {
            // If in either happiness ass unhappy, then it will be unhappy
            if (std::get<1>(secondaryEntry).getHappiness(vertex) == HappinessValue::happy)
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
                    mergedHappiness.setHappiness(vertex, HappinessValue::happy);
                }
                else
                {
                    mergedHappiness.setHappiness(vertex, HappinessValue::unhappy);
                }
            }
            else
            {
                mergedHappiness.setHappiness(vertex, HappinessValue::unhappy);
            }
        }
    }

    // Add colouring
    ranking.push(mergedColouring, mergedHappiness, getEvaluation(mergedHappiness));
}

