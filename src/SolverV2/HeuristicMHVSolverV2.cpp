//
// Created by louis on 17/03/2022.
//

#include <algorithm>
#include "HeuristicMHVSolverV2.h"
#include "../DataStructures/Evaluator/BasicMHVEvaluator.h"
#include "../rng.h"

SolverV2::HeuristicMHVSolverV2::HeuristicMHVSolverV2(
        int nbSolutionsToKeep,
        int weightHappyVertices,
        int weightPotentialHappyVertices,
        int weightUnhappyVertices,
        int weightPotentialUnhappyVertices,
        JoinNodeRankingOrder joinNodeRankingOrder,
        VertexWeightJoinBag vertexWeightJoinBag,
        JoinNodeCombineHeuristic joinNodeCombineHeuristic)
    : nbSolutionsToKeep(nbSolutionsToKeep),
      weightHappyVertices{weightHappyVertices},
      weightPotentialHappyVertices{weightPotentialHappyVertices},
      weightUnhappyVertices{weightUnhappyVertices},
      weightPotentialUnhappyVertices{weightPotentialUnhappyVertices},
      joinNodeRankingOrder{joinNodeRankingOrder},
      vertexWeightJoinBag{vertexWeightJoinBag},
      joinNodeCombineHeuristic{joinNodeCombineHeuristic}
{ }

bool SolverV2::HeuristicMHVSolverV2::hasFoundExactSolution() const
{
    return foundExactSolution;
}

void SolverV2::HeuristicMHVSolverV2::solve(
        std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition)
{
    // Assume an exact solution is found until it is shown otherwise
    foundExactSolution = true;

//    std::cout << *treeDecomposition << "\n"; // TODO remove commented code
//    for (auto v{0}; v < graph->getNbVertices(); v++)
//    {
//        std::cout << "Neighbours of " << v << ": ";
//        for (auto n : graph->getNeighbours(v)) std::cout << n << ", ";
//        std::cout << "\n";
//    }
//    std::cout << "Initial colouring: " << graph->getColourString() << "\n";

    // Find the partial solutions from the root node
    HeuristicSolverRankingV2 ranking = solveAtNode(treeDecomposition->getRoot(), graph);

    // Retrieve the best entry
    HeuristicSolverRankingV2::Entry bestEntry = ranking.getBestEntry();

    // Colour graph
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!graph->isPrecoloured(vertex))
            graph->setColour(vertex, std::get<0>(bestEntry).getColour(vertex));
    }


    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++) // TODO remove commented code
    {
        if (!graph->isColoured(vertex))
            std::cout << "Vertex " << vertex << " is not coloured!\n";
    }

    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (std::get<1>(bestEntry).getHappiness(vertex) == HappinessValue::unhappy)
        {
            if (std::all_of(
                    graph->getNeighbours(vertex).begin(),
                    graph->getNeighbours(vertex).end(),
                    [bestEntry, vertex](DataStructures::VertexType neighbour)
                    {
                        return std::get<0>(bestEntry).getColour(neighbour) == std::get<0>(bestEntry).getColour(vertex);
                    }))
            {
                std::cout << "Vertex " << vertex << " is set unhappy but all neighbours have same colour\n";
                std::cout << vertex << " is precoloured: " << std::boolalpha << graph->isPrecoloured(vertex) << "\n";
            }
        }
        else if (std::get<1>(bestEntry).getHappiness(vertex) == HappinessValue::happy)
        {
            if (std::any_of(
                    graph->getNeighbours(vertex).begin(),
                    graph->getNeighbours(vertex).end(),
                    [bestEntry, vertex](DataStructures::VertexType neighbour)
                    {
                        return std::get<0>(bestEntry).getColour(neighbour) != std::get<0>(bestEntry).getColour(vertex);
                    }))
            {
                std::cout << "Vertex " << vertex << " is set happy but has differently coloured neighbour\n";
                std::cout << vertex << " is precoloured: " << std::boolalpha << graph->isPrecoloured(vertex) << "\n";
            }
        }
        else
        {
            std::cout << "Vertex " << vertex << " is neither happy nor unhappy in the final entry.\n";
        }
    }
}

DataStructures::VertexType vertexToCheck = 86;

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::solveAtNode(
        const std::shared_ptr<DataStructures::NiceNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    switch(node->getNodeType())
    {
        case DataStructures::NodeType::LeafNode:
        {
            HeuristicSolverRankingV2 ranking = handleLeafNode(std::dynamic_pointer_cast<DataStructures::LeafNode>(node), graph);
            if (ranking.hasReachedCapacity()) foundExactSolution = false;
//            std::cout << "Ranking at leaf node " << node->getId() << ":\n" << ranking << "\n";
            return ranking;
        }
        case DataStructures::NodeType::IntroduceNode:
        {
            HeuristicSolverRankingV2 ranking = handleIntroduceNode(std::dynamic_pointer_cast<DataStructures::IntroduceNode>(node), graph);
            if (ranking.hasReachedCapacity()) foundExactSolution = false;
//            std::cout << "Ranking at introduce node " << node->getId() << ":\n" << ranking << "\n";

//            DataStructures::VertexType introducedVertex = std::dynamic_pointer_cast<DataStructures::IntroduceNode>(node)->getIntroducedVertex();
//            if (introducedVertex == vertexToCheck)
//            {
//                for (const HeuristicSolverRankingV2::Entry& entry : ranking)
//                {
//                    if (std::any_of(
//                            graph->getNeighbours(introducedVertex).begin(),
//                            graph->getNeighbours(introducedVertex).end(),
//                            [entry, introducedVertex](DataStructures::VertexType neighbour)
//                            {
//                                return std::get<0>(entry).isColoured(neighbour) && std::get<0>(entry).getColour(introducedVertex) != std::get<0>(entry).getColour(neighbour);
//                            }))
//                    {
//                        if (std::get<1>(entry).getHappiness(introducedVertex) == HappinessValue::happy)
//                        {
//                            std::cout << "Introduced vertex " << introducedVertex << " is happy but has differently coloured neighbour!\n";
//                        }
//                    }
//                }
//            }

            return ranking;
        }
        case DataStructures::NodeType::ForgetNode:
        {
            HeuristicSolverRankingV2 ranking = handleForgetNode(std::dynamic_pointer_cast<DataStructures::ForgetNode>(node), graph);
            if (ranking.hasReachedCapacity()) foundExactSolution = false;
//            std::cout << "Ranking at forget node " << node->getId() << ":\n" << ranking << "\n";

//            DataStructures::VertexType forgottenVertex = std::dynamic_pointer_cast<DataStructures::ForgetNode>(node)->getForgottenVertex();
//            if (forgottenVertex == vertexToCheck)
//            {
//                for (const HeuristicSolverRankingV2::Entry& entry : ranking)
//                {
//                    if (std::any_of(
//                            graph->getNeighbours(forgottenVertex).begin(),
//                            graph->getNeighbours(forgottenVertex).end(),
//                            [entry, forgottenVertex](DataStructures::VertexType neighbour)
//                            {
//                                return std::get<0>(entry).getColour(forgottenVertex) != std::get<0>(entry).getColour(neighbour);
//                            }))
//                    {
//                        if (std::get<1>(entry).getHappiness(forgottenVertex) == HappinessValue::happy) // All it's neighbours should be coloured
//                        {
//                            std::cout << "-------------------------------------------------\n";
//                            std::cout << "Colour of forgotten vertex " << forgottenVertex << ": " << std::get<0>(entry).getColour(forgottenVertex);
//                            std::cout << " [precoloured=" << std::boolalpha << graph->isPrecoloured(forgottenVertex) << "]\n";
//                            for (DataStructures::VertexType neighbour : graph->getNeighbours(forgottenVertex))
//                            {
//                                std::cout << "Colour of neighbour " << neighbour << ": " << std::get<0>(entry).getColour(neighbour);
//                                std::cout << " [precoloured=" << std::boolalpha << graph->isPrecoloured(neighbour) << "]\n";
//                            }
//
//                            std::cout << "Forgotten vertex " << forgottenVertex << " is happy but has differently coloured neighbour!\n";
//                            std::cout << *node << "\n";
//                            throw std::runtime_error("STOP, HAMMERTIME!");
//                        }
//                    }
//                }
//            }
            return ranking;
        }
        case DataStructures::NodeType::JoinNode:
        {
            HeuristicSolverRankingV2 ranking = handleJoinNode(std::dynamic_pointer_cast<DataStructures::JoinNode>(node), graph);
            if (ranking.hasReachedCapacity()) foundExactSolution = false;
//            std::cout << "Ranking at join node " << node->getId() << ":\n" << ranking << "\n";
            return ranking;
        }
    }
}

int SolverV2::HeuristicMHVSolverV2::getEvaluation(const HappyVertexAssignmentV2& happyVertexAssignment) const
{
    return weightHappyVertices * happyVertexAssignment.getCountOf(HappinessValue::happy) +
           weightPotentialHappyVertices * happyVertexAssignment.getCountOf(HappinessValue::potentiallyHappy) +
           weightUnhappyVertices * happyVertexAssignment.getCountOf(HappinessValue::unhappy) +
           weightPotentialUnhappyVertices * happyVertexAssignment.getCountOf(HappinessValue::potentiallyUnhappy);
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleLeafNode(
        const std::shared_ptr<DataStructures::LeafNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph) const
{
    // Create an empty ranking
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};
    ranking.push(ColourAssignmentV2{graph}, HappyVertexAssignmentV2{graph}, 0);
    return ranking;
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleIntroduceNode(
        const std::shared_ptr<DataStructures::IntroduceNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    // Find the solutions for the child node
    HeuristicSolverRankingV2 rankingChild = solveAtNode(node->getChild(), graph);

    // Create an empty ranking and backup ranking
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};
    HeuristicSolverRankingV2 backupRanking{nbSolutionsToKeep};

    HeuristicSolverRankingV2::Entry firstEntry = *rankingChild.begin();

    // Classify the neighbours of the introduced vertex
    std::vector<DataStructures::VertexType> colouredNeighbours{};
    std::vector<DataStructures::VertexType> precolouredNeighbours{};
    std::vector<DataStructures::VertexType> uncolouredNeighbours{};
    for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
    {
        if (std::get<0>(firstEntry).isColoured(neighbour))
        {
            colouredNeighbours.push_back(neighbour);
        }
        else if (graph->isPrecoloured(neighbour))
        {
            precolouredNeighbours.push_back(neighbour);
        }
        else
        {
            uncolouredNeighbours.push_back(neighbour);
        }
    }

    std::vector<DataStructures::VertexType> neighboursWithAllNeighboursColoured{};
    for (DataStructures::VertexType vertex : colouredNeighbours)
    {
        if (std::all_of(
                graph->getNeighbours(vertex).begin(),
                graph->getNeighbours(vertex).end(),
                [firstEntry, node](DataStructures::VertexType neighbour)
                {
                    return std::get<0>(firstEntry).isColoured(neighbour) || neighbour == node->getIntroducedVertex();
                }))
        {
            neighboursWithAllNeighboursColoured.push_back(vertex);
        }
    }

    for (const HeuristicSolverRankingV2::Entry& entry : rankingChild)
    {
        // An assignment based on the happiness assignment of the child
        HappyVertexAssignmentV2 happyVertexAssignmentWithNeighbours{std::get<1>(entry)};

        // A map of neighbours onto the colour that is currently makes them potentially happy
        // Thus if the introduced vertex receives that colour, the vertex remains potentially happy, and otherwise
        // it becomes unhappy
        std::map<DataStructures::VertexType, DataStructures::ColourType> potentialHappyNeighbours{};

        // Check if all the coloured and happy neighbours have the same colour
        std::set<DataStructures::ColourType> coloursHappyNeighbours{};
        std::set<DataStructures::ColourType> coloursNeighbours{}; // TODO needed?
        for (DataStructures::VertexType colouredNeighbour : colouredNeighbours)
        {
            coloursNeighbours.insert(std::get<0>(entry).getColour(colouredNeighbour));
            if (std::get<1>(entry).getHappiness(colouredNeighbour) == HappinessValue::happy)
            {
                coloursHappyNeighbours.insert(std::get<0>(entry).getColour(colouredNeighbour));
            }
        }

        // Check the happiness of all precoloured vertices that are not coloured in the oclouring yet
        for (DataStructures::VertexType precolouredNeighbour : precolouredNeighbours)
        {
            coloursNeighbours.insert(graph->getColour(precolouredNeighbour));
            if (std::get<1>(entry).getHappiness(precolouredNeighbour) == HappinessValue::potentiallyHappy)
            {
                // If the vertex is potentially happy, then it will only remain potentially happy if the introduced
                // vertex is coloured in the predefined colour
                potentialHappyNeighbours.insert(std::make_pair(precolouredNeighbour, graph->getColour(precolouredNeighbour)));
            }
            else if (std::get<1>(entry).getHappiness(precolouredNeighbour) == HappinessValue::unknown)
            {
                // If the happiness of the precoloured vertex is unknown, but if any of its neighbours is precoloured in
                // a different colour, then it will be unhappy in any colouring
                if (std::any_of(
                        graph->getNeighbours(precolouredNeighbour).begin(),
                        graph->getNeighbours(precolouredNeighbour).end(),
                        [graph, precolouredNeighbour](DataStructures::VertexType neighbourOfNeighbour)
                        {
                            return graph->isPrecoloured(neighbourOfNeighbour) && graph->getColour(neighbourOfNeighbour) != graph->getColour(precolouredNeighbour);
                        }))
                {
                    happyVertexAssignmentWithNeighbours.setHappiness(precolouredNeighbour, HappinessValue::unhappy);
                }
                else
                {
                    potentialHappyNeighbours.insert(std::make_pair(precolouredNeighbour, graph->getColour(precolouredNeighbour)));
                }
            }
        }

        // Check the happiness of all uncoloured neighbours of the introduced vertex
        for (DataStructures::VertexType uncolouredNeighbour : uncolouredNeighbours)
        {
            if (std::get<1>(entry).getHappiness(uncolouredNeighbour) == HappinessValue::potentiallyHappy)
            {
                // If the vertex is potentially happy, then it has neighbours of only one colour, that is both
                // the vertices coloured in the colouring and the vertices that are precoloured
                for (DataStructures::VertexType neighbourOfNeighbour : graph->getNeighbours(uncolouredNeighbour))
                {
                    // If the neighbour is connected to any vertex that is precoloured but not coloured in the colouring,
                    // then that precoloured vertex must have the same colour as the other connected vertices already
                    // coloured because otherwise neighbour would be unhappy
                    if (std::get<0>(entry).isColoured(neighbourOfNeighbour))
                    {
                        potentialHappyNeighbours.insert(std::make_pair(uncolouredNeighbour, std::get<0>(entry).getColour(neighbourOfNeighbour)));
                        break;
                    }
                    else if (graph->isPrecoloured(neighbourOfNeighbour))
                    {
                        potentialHappyNeighbours.insert(std::make_pair(uncolouredNeighbour, graph->getColour(neighbourOfNeighbour)));
                        break;
                    }
                }
            }
            else if (std::get<1>(entry).getHappiness(uncolouredNeighbour) == HappinessValue::unknown)
            {
                // If the uncoloured vertex has no known type, then it can't have any neighbours that are already coloured
                // because then it would receive some happiness, but it can have pre coloured neighbours which decide its
                // happiness
                DataStructures::ColourType colourOfPrecolouredNeighboursOfNeighbour{0};
                bool precolouredNeighboursHaveOnlyOneColour{true};
                for (DataStructures::VertexType neighbourOfNeighbour : graph->getNeighbours(uncolouredNeighbour))
                {
                    if (graph->isPrecoloured(neighbourOfNeighbour))
                    {
                        if (colourOfPrecolouredNeighboursOfNeighbour == 0)
                        {
                            colourOfPrecolouredNeighboursOfNeighbour = graph->getColour(neighbourOfNeighbour);
                        }
                        else if (colourOfPrecolouredNeighboursOfNeighbour != graph->getColour(neighbourOfNeighbour))
                        {
                            precolouredNeighboursHaveOnlyOneColour = false;
                            break;
                        }
                    }
                }

                // Set the happiness of the unknown+uncoloured neighbour depending on the colour(s) of its precoloured
                // neighbours
                if (precolouredNeighboursHaveOnlyOneColour)
                {
                    if (colourOfPrecolouredNeighboursOfNeighbour == 0)
                    {
                        // If there is no precoloured neighbour, then it will always be potentially happy, no matter
                        // the colour of the introduced vertex
                        happyVertexAssignmentWithNeighbours.setHappiness(uncolouredNeighbour, HappinessValue::potentiallyHappy);
                    }
                    else
                    {
                        // The precoloured neighbours have only a single colour, thus the vertex will be potentially
                        // happy only if the introduced node is coloured in that same colour
                        potentialHappyNeighbours.insert(std::make_pair(uncolouredNeighbour, colourOfPrecolouredNeighboursOfNeighbour));
                    }
                }
                else
                {
                    // If the precoloured vertices have multiple colours, then the vertex is destined to be unhappy
                    happyVertexAssignmentWithNeighbours.setHappiness(uncolouredNeighbour, HappinessValue::unhappy);
                }
            }
        }

        // Check which colours can make the introduced vertex happy
        std::set<DataStructures::ColourType> coloursThatMakeIntroducedVertexHappy{};
        if (std::get<1>(entry).getHappiness(node->getIntroducedVertex()) == HappinessValue::potentiallyHappy)
        {
            // If the introduced vertex is potentially happy, then the vertex can be made happy
            // The assignment of the neighbouring colour can not conflict with any already coloured vertex because the
            // neighbours all have the same colour due to the 'potential happiness'
            // Even if the introduced vertex is pre coloured, it still can be made happy because if the vertex was
            // precoloured differently than any of its neighbours it would be unhappy
            coloursThatMakeIntroducedVertexHappy.insert(std::get<0>(entry).getColour(*colouredNeighbours.begin()));
        }
        else if (colouredNeighbours.empty())
        {
            if (precolouredNeighbours.empty())
            {
                // If the vertex is not potentially happy and has no precoloured neighbours, then every colour can make it happy
                for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
                {
                    coloursThatMakeIntroducedVertexHappy.insert(coloursThatMakeIntroducedVertexHappy.end(), colour);
                }
            }
            else
            {
                // If the vertex has precoloured neighbours, then it can only be happy if those neighbours have the same colour
                // and if it is coloured in that colour
                for (DataStructures::VertexType precolouredNeighbour : precolouredNeighbours)
                {
                    coloursThatMakeIntroducedVertexHappy.insert(graph->getColour(precolouredNeighbour));
                    if (coloursThatMakeIntroducedVertexHappy.size() > 1)
                    {
                        coloursThatMakeIntroducedVertexHappy.clear();
                        break;
                    }
                }
            }
        }

        // Make the vertex happy for all the colours for which that is possible
        for (DataStructures::ColourType colourForIntroducedVertex : coloursThatMakeIntroducedVertexHappy)
        {
            // If the introduced vertex is precoloured, then only use that colour
            if (graph->isPrecoloured(node->getIntroducedVertex()) && colourForIntroducedVertex != graph->getColour(node->getIntroducedVertex())) continue;

            // The introduced vertex can be made happy by colouring it in the colourForIntroducedVertex of the neighbours
            ColourAssignmentV2 colourAssignment{std::get<0>(entry)};
            colourAssignment.setColour(node->getIntroducedVertex(), colourForIntroducedVertex);

            // Check the vertices that were potentially happy to see if they can still be happy
            HappyVertexAssignmentV2 happyVertexAssignment{happyVertexAssignmentWithNeighbours};
            happyVertexAssignment.setHappiness(node->getIntroducedVertex(), HappinessValue::happy);
            for (const auto& [potentiallyHappyNeighbour, colourPotentiallyHappyNeighbour] : potentialHappyNeighbours)
            {
                if (colourForIntroducedVertex == colourPotentiallyHappyNeighbour)
                    happyVertexAssignment.setHappiness(potentiallyHappyNeighbour, HappinessValue::potentiallyHappy);
                else
                    happyVertexAssignment.setHappiness(potentiallyHappyNeighbour, HappinessValue::unhappy);
            }

            // If a neighbour of which all its neighbours are coloured is potentially happy, then it can be made happy
            // We don't need to check the colour because if it had a different colour then the introduced vertex could
            // not be made happy
            for (DataStructures::VertexType vertex : neighboursWithAllNeighboursColoured)
            {
                if (happyVertexAssignment.getHappiness(vertex) == HappinessValue::potentiallyUnhappy)
                {
                    happyVertexAssignment.setHappiness(vertex, HappinessValue::happy);
                }
            }

            // Push the new entry
            ranking.push(colourAssignment, happyVertexAssignment, getEvaluation(happyVertexAssignment));
        }

        // If there are no uncoloured neighbours and all neighbours have the same colour, then there is no need to make the vertex unhappy
        if (uncolouredNeighbours.empty() && precolouredNeighbours.empty() && !graph->isPrecoloured(node->getIntroducedVertex()))
        {
            if (colouredNeighbours.empty()) continue;

            DataStructures::ColourType colourNeighbours = std::get<0>(entry).getColour(colouredNeighbours.front());

            if (std::all_of(
                    graph->getNeighbours(node->getIntroducedVertex()).begin(),
                    graph->getNeighbours(node->getIntroducedVertex()).end(),
                    [entry, colourNeighbours](DataStructures::VertexType neighbour)
                    {
                        return std::get<0>(entry).getColour(neighbour) == colourNeighbours;
                    }))
            {
                continue;
            }
        }

        // All the colours can be used to make the vertex unhappy
        for (DataStructures::ColourType colourForIntroducedVertex{1}; colourForIntroducedVertex <= graph->getNbColours(); colourForIntroducedVertex++)
        {
            // If the introduced vertex is precoloured, then only use that colour
            if (graph->isPrecoloured(node->getIntroducedVertex()) && colourForIntroducedVertex != graph->getColour(node->getIntroducedVertex())) continue;

            // If any of the happy neighbours has a different colour, the colour can't be used because the neighbour can't be happy
            if (std::any_of(
                    coloursHappyNeighbours.begin(),
                    coloursHappyNeighbours.end(),
                    [colourForIntroducedVertex](DataStructures::ColourType otherColour){ return colourForIntroducedVertex != otherColour; }))
            {
                // If a valid entry has already been generated, then there is no need to compute a new, backup entry
                if (ranking.size() > 0) continue;

                // Create a new colouring and colour the forgotten vertex
                ColourAssignmentV2 colourAssignment{std::get<0>(entry)};
                colourAssignment.setColour(node->getIntroducedVertex(), colourForIntroducedVertex);

                // Make the introduced vertex unhappy, as well as all coloured neighbours that have a different colour
                HappyVertexAssignmentV2 happyVertexAssignment{happyVertexAssignmentWithNeighbours};
                happyVertexAssignment.setHappiness(node->getIntroducedVertex(), HappinessValue::unhappy);
                for (DataStructures::VertexType neighbour : colouredNeighbours)
                {
                    if ((std::get<1>(entry).getHappiness(neighbour) == HappinessValue::happy ||
                        std::get<1>(entry).getHappiness(neighbour) == HappinessValue::potentiallyUnhappy) &&
                        std::get<0>(entry).getColour(neighbour) != colourForIntroducedVertex)
                    {
                        happyVertexAssignment.setHappiness(neighbour, HappinessValue::unhappy);
                    }
                }

                // Check for vertices that could be potentially happy
                for (const auto& [potentiallyHappyNeighbour, colourPotentiallyHappyNeighbour] : potentialHappyNeighbours)
                {
                    if (colourForIntroducedVertex == colourPotentiallyHappyNeighbour)
                        happyVertexAssignment.setHappiness(potentiallyHappyNeighbour, HappinessValue::potentiallyHappy);
                    else
                        happyVertexAssignment.setHappiness(potentiallyHappyNeighbour, HappinessValue::unhappy);
                }

                // Check the vertices with no uncoloured neighbours, if they can are potentially unhappy they can become happy
                // We don't need to make them unhappy if they have a different colour because that is covered in a previous loop
                for (DataStructures::VertexType vertex : neighboursWithAllNeighboursColoured)
                {
                    if (happyVertexAssignment.getHappiness(vertex) == HappinessValue::potentiallyUnhappy &&
                        std::get<0>(entry).getColour(vertex) == colourForIntroducedVertex)
                    {
                        happyVertexAssignment.setHappiness(vertex, HappinessValue::happy);
                    }
                }

                // Add the new entry to the backup ranking
                backupRanking.push(colourAssignment, happyVertexAssignment, getEvaluation(happyVertexAssignment));
            }
            else
            {
                // The introduced vertex can be made happy by colouring it in the colourForIntroducedVertex of the neighbours
                ColourAssignmentV2 colourAssignment{std::get<0>(entry)};
                colourAssignment.setColour(node->getIntroducedVertex(), colourForIntroducedVertex);

                // Check the vertices that were potentially happy to see if they can still be happy
                HappyVertexAssignmentV2 happyVertexAssignment{happyVertexAssignmentWithNeighbours};

                // If any of the happy neighbours has a different colour, the colour can't be used because the neighbour can't be happy
                if (std::any_of( // TODO maybe this check costs some time?
                        coloursNeighbours.begin(),
                        coloursNeighbours.end(),
                        [colourForIntroducedVertex](DataStructures::ColourType otherColour){ return colourForIntroducedVertex != otherColour; })
                    ||
                    std::any_of(
                            precolouredNeighbours.begin(),
                            precolouredNeighbours.end(),
                            [colourForIntroducedVertex](DataStructures::ColourType otherColour){ return colourForIntroducedVertex != otherColour; }))
                {
                    happyVertexAssignment.setHappiness(node->getIntroducedVertex(), HappinessValue::unhappy);
                }
                else
                {
                    happyVertexAssignment.setHappiness(node->getIntroducedVertex(), HappinessValue::potentiallyUnhappy);
                }

//                happyVertexAssignment.setHappiness(node->getIntroducedVertex(), HappinessValue::unhappy);


                for (const auto& [potentiallyHappyNeighbour, colourPotentiallyHappyNeighbour] : potentialHappyNeighbours)
                {
                    if (colourForIntroducedVertex == colourPotentiallyHappyNeighbour)
                        happyVertexAssignment.setHappiness(potentiallyHappyNeighbour, HappinessValue::potentiallyHappy);
                    else
                        happyVertexAssignment.setHappiness(potentiallyHappyNeighbour, HappinessValue::unhappy);
                }

                for (DataStructures::VertexType vertex : colouredNeighbours)
                {
                    if (happyVertexAssignment.getHappiness(vertex) == HappinessValue::potentiallyUnhappy &&
                        colourForIntroducedVertex != colourAssignment.getColour(vertex))
                    {
                        happyVertexAssignment.setHappiness(vertex, HappinessValue::unhappy);
                    }
                }

                for (DataStructures::VertexType vertex : neighboursWithAllNeighboursColoured)
                {
                    if (happyVertexAssignment.getHappiness(vertex) == HappinessValue::potentiallyUnhappy)
                    {
                        if (colourForIntroducedVertex == colourAssignment.getColour(vertex))
                        {
                            happyVertexAssignment.setHappiness(vertex, HappinessValue::happy);
                        }
                        else
                        {
                            happyVertexAssignment.setHappiness(vertex, HappinessValue::unhappy);
                        }
                    }
                }

                // Push the new entry
                ranking.push(colourAssignment, happyVertexAssignment, getEvaluation(happyVertexAssignment));
            }
        }
    }

    // Return the ranking, but if no valid entry has been constructed, return the backup ranking
    if (ranking.size() > 0)
        return ranking;
    else
        return backupRanking;
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleForgetNode(
        const std::shared_ptr<DataStructures::ForgetNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    // Compute the ranking for the child node
    HeuristicSolverRankingV2 rankingChild = solveAtNode(node->getChild(), graph);

    // A set to keep track of the unique entries to add, that is the entries with unique colour and happiness for
    // the vertices in the node's bag
    auto comparator =
            [node]
            (const HeuristicSolverRankingV2::Entry& e1, const HeuristicSolverRankingV2::Entry& e2)
            {
                for (DataStructures::VertexType vertex : node->getBagContent())
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
        const std::shared_ptr<DataStructures::Graph>& graph)
{
    // Compute the ranking for the child nodes
    HeuristicSolverRankingV2 rankingLeftChild = solveAtNode(node->getLeftChild(), graph);
    HeuristicSolverRankingV2 rankingRightChild = solveAtNode(node->getRightChild(), graph);

    // Create a new empty ranking and backup ranking
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};
    HeuristicSolverRankingV2 backupRanking{nbSolutionsToKeep};

    // Check which ranking should be in the outer loop and which should be in the inner loop
    HeuristicSolverRankingV2* outerRanking;
    HeuristicSolverRankingV2* innerRanking;
    switch (joinNodeRankingOrder)
    {
        case JoinNodeRankingOrder::largestRankingOut:
        {
            if (rankingLeftChild.size() > rankingRightChild.size())
            {
                outerRanking = &rankingLeftChild;
                innerRanking = &rankingRightChild;
            }
            else
            {
                outerRanking = &rankingRightChild;
                innerRanking = &rankingLeftChild;
            }
            break;
        }
        case JoinNodeRankingOrder::smallestRankingOut:
        {
            if (rankingLeftChild.size() > rankingRightChild.size())
            {
                outerRanking = &rankingRightChild;
                innerRanking = &rankingLeftChild;
            }
            else
            {
                outerRanking = &rankingLeftChild;
                innerRanking = &rankingRightChild;
            }
            break;
        }
        case JoinNodeRankingOrder::randomRankingOut:
        {
            std::uniform_real_distribution<> dist(0, 1);
            if (dist(RNG::rng) < 0.5)
            {
                outerRanking = &rankingRightChild;
                innerRanking = &rankingLeftChild;
            }
            else
            {
                outerRanking = &rankingLeftChild;
                innerRanking = &rankingRightChild;
            }
            break;
        }
    }

    // Compute the weight for all vertices for how much they must be taking into account for matching
    std::map<DataStructures::VertexType, int> verticesAndWeight{};
    switch (vertexWeightJoinBag)
    {
        case VertexWeightJoinBag::unitary:
        {
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                verticesAndWeight.insert(verticesAndWeight.end(), std::make_pair(vertex, 1));
            }
            break;
        }
        case VertexWeightJoinBag::nbColouredNeighboursOutsideBag:
        {
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                verticesAndWeight.insert(verticesAndWeight.end(),
                    std::make_pair(
                        vertex,
                        std::count_if(
                            graph->getNeighbours(vertex).begin(),
                            graph->getNeighbours(vertex).end(),
                            [outerRanking, innerRanking](DataStructures::VertexType neighbour)
                            {
                                return std::get<0>(*outerRanking->begin()).isColoured(neighbour) != std::get<0>(*innerRanking->begin()).isColoured(neighbour);
                            })
                    ));
            }
            break;
        }
        case VertexWeightJoinBag::hasColouredNeighbourOutsideBag:
        {
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                verticesAndWeight.insert(verticesAndWeight.end(),
                    std::make_pair(
                        vertex,
                        std::any_of(
                            graph->getNeighbours(vertex).begin(),
                            graph->getNeighbours(vertex).end(),
                            [outerRanking, innerRanking](DataStructures::VertexType neighbour)
                            {
                                return std::get<0>(*outerRanking->begin()).isColoured(neighbour) != std::get<0>(*innerRanking->begin()).isColoured(neighbour);
                            })
                        ));
            }
            break;
        }
        case VertexWeightJoinBag::nbNeighboursOutsideBag:
        {
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                verticesAndWeight.insert(verticesAndWeight.end(),
                    std::make_pair(
                        vertex,
                        std::count_if(
                            graph->getNeighbours(vertex).begin(),
                            graph->getNeighbours(vertex).end(),
                            [outerRanking, innerRanking](DataStructures::VertexType neighbour)
                            {
                                return !std::get<0>(*outerRanking->begin()).isColoured(neighbour) || !std::get<0>(*innerRanking->begin()).isColoured(neighbour);
                            })
                        ));
            }
            break;
        }
        case VertexWeightJoinBag::hasNeighboursOutsideBag:
        {
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                verticesAndWeight.insert(verticesAndWeight.end(),
                    std::make_pair(
                        vertex,
                        std::any_of(
                            graph->getNeighbours(vertex).begin(),
                            graph->getNeighbours(vertex).end(),
                            [outerRanking, innerRanking](DataStructures::VertexType neighbour)
                            {
                                return !std::get<0>(*outerRanking->begin()).isColoured(neighbour) || !std::get<0>(*innerRanking->begin()).isColoured(neighbour);
                            })
                        ));
            }
            break;
        }
        case VertexWeightJoinBag::nbNeighboursInBorder:
        {
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                verticesAndWeight.insert(verticesAndWeight.end(),
                    std::make_pair(
                        vertex,
                        std::count_if(
                            graph->getNeighbours(vertex).begin(),
                            graph->getNeighbours(vertex).end(),
                            [outerRanking, innerRanking](DataStructures::VertexType neighbour)
                            {
                                return !std::get<0>(*outerRanking->begin()).isColoured(neighbour) && !std::get<0>(*innerRanking->begin()).isColoured(neighbour);
                            })
                        ));
            }
            break;
        }
        case VertexWeightJoinBag::hasNeighbourInBorder:
        {
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                verticesAndWeight.insert(verticesAndWeight.end(),
                 std::make_pair(
                     vertex,
                     std::any_of(
                         graph->getNeighbours(vertex).begin(),
                         graph->getNeighbours(vertex).end(),
                         [outerRanking, innerRanking](DataStructures::VertexType neighbour)
                         {
                             return !std::get<0>(*outerRanking->begin()).isColoured(neighbour) && !std::get<0>(*innerRanking->begin()).isColoured(neighbour);
                         })
                    ));
            }
            break;
        }
    }

    // Find the vertices that are bordering the bag
    std::set<DataStructures::VertexType> verticesBorder{};
    std::set<DataStructures::VertexType> verticesBorderOuter{};
    std::set<DataStructures::VertexType> verticesBagConnectingOuter{};
    std::set<DataStructures::VertexType> verticesBorderInner{};
    std::set<DataStructures::VertexType> verticesBagConnectingInner{};
    for (DataStructures::VertexType vertex : node->getBagContent())
    {
        bool neighbourInOuter{false};
        bool neighbourInInner{false};
        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (!std::get<0>(*outerRanking->begin()).isColoured(neighbour) && !std::get<0>(*innerRanking->begin()).isColoured(neighbour))
            {
                verticesBorder.insert(neighbour);
            }
            else if (std::get<0>(*outerRanking->begin()).isColoured(neighbour) && !std::get<0>(*innerRanking->begin()).isColoured(neighbour))
            {
                verticesBorderOuter.insert(neighbour);
                neighbourInOuter = true;
            }
            else if (!std::get<0>(*outerRanking->begin()).isColoured(neighbour) && std::get<0>(*innerRanking->begin()).isColoured(neighbour))
            {
                verticesBorderInner.insert(neighbour);
                neighbourInInner = true;
            }
        }
        if (neighbourInOuter)
        {
            verticesBagConnectingOuter.insert(vertex); // TODO can be queue?
        }
        if (neighbourInInner)
        {
            verticesBagConnectingInner.insert(vertex); // TODO can be queue?
        }
    }

    // For each entry in the outer ranking, try to find a match
    for (const HeuristicSolverRankingV2::Entry& entryOuterLoop : *outerRanking)
    {
        // Keep track of the best entry in the inner ranking in case no match is found
        int bestNbMistakes = 2 * node->getBagSize();
        HeuristicSolverRankingV2::Entry bestEntryInnerLoop = *innerRanking->begin();

        // Check which entry in the inner ranking matches the entry in the outer ranking
        bool foundMatch{false};
        for (const HeuristicSolverRankingV2::Entry& entryInnerLoop : *innerRanking)
        {
            // Check if all the vertices in the bag are equal or not
            bool hasDifferenceInBag{false};
            int nbMistakes{0};
            for (const std::pair<const DataStructures::VertexType, int>& vertexWeight : verticesAndWeight)
            {
                // Check if there is a mistake in the colouring
                if (std::get<0>(entryOuterLoop).getColour(vertexWeight.first) != std::get<0>(entryInnerLoop).getColour(vertexWeight.first))
                {
                    hasDifferenceInBag = true;
                    if (ranking.size() > 0) break;
                    nbMistakes += vertexWeight.second;
                }
                // Check if there is a mistake in the happiness
                if (std::get<1>(entryOuterLoop).getHappiness(vertexWeight.first) != std::get<1>(entryInnerLoop).getHappiness(vertexWeight.first))
                {
                    hasDifferenceInBag = true;
                    if (ranking.size() > 0) break;
                    nbMistakes += vertexWeight.second;
                }
            }

            // If there are no mistakes, then a match has been found
            if (!hasDifferenceInBag)
            {
                // Merge the happiness of the two entries
                HappyVertexAssignmentV2 mergedHappiness{std::get<1>(entryOuterLoop)};
                for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
                {
                    if (!std::get<0>(entryOuterLoop).isColoured(vertex) && std::get<0>(entryInnerLoop).isColoured(vertex))
                    {
                        mergedHappiness.setHappiness(vertex, std::get<1>(entryInnerLoop).getHappiness(vertex));
                    }
                }

                // Push the merged happiness and a merged colouring to the ranking
                ranking.push(
                        ColourAssignmentV2{std::get<0>(entryOuterLoop), std::get<0>(entryInnerLoop)},
                        mergedHappiness,
                        getEvaluation(mergedHappiness));

                // A match has been found, thus the best nb mistakes is 0, and we don't have to look for a new match anymore
                foundMatch = true;
                break;
            }

            // If the number of mistakes is better than the best number of mistakes, a better match has been found
            if (nbMistakes < bestNbMistakes)
            {
                bestNbMistakes = nbMistakes;
                bestEntryInnerLoop = entryInnerLoop;
            }
        }

        // In case no perfect match was found and no valid entry has been computed yet, merge the outer entry with the most matching inner entry
        if (!foundMatch && ranking.size() == 0)
        {
            switch (joinNodeCombineHeuristic)
            {
                case JoinNodeCombineHeuristic::copyBag:
                {
                    copyBag(backupRanking, node, graph,
                            entryOuterLoop, bestEntryInnerLoop,
                            verticesBorderInner, verticesBagConnectingInner);
                    copyBag(backupRanking, node, graph,
                            bestEntryInnerLoop, entryOuterLoop,
                            verticesBorderOuter, verticesBagConnectingOuter);
                    break;
                }
                case JoinNodeCombineHeuristic::merge:
                {
                    merge(backupRanking, node, graph,
                          bestEntryInnerLoop, entryOuterLoop,
                          verticesBorder, verticesBorderInner, verticesBorderOuter);
                    break;
                }
            }
        }
    }

    // Return the final ranking
    if (ranking.size() > 0)
        return ranking;
    else
        return backupRanking;
}

void SolverV2::HeuristicMHVSolverV2::copyBag(
        SolverV2::HeuristicSolverRankingV2& ranking,
        const std::shared_ptr<DataStructures::JoinNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph,
        const SolverV2::HeuristicSolverRankingV2::Entry& primaryEntry,
        const SolverV2::HeuristicSolverRankingV2::Entry& secondaryEntry,
        const std::set<DataStructures::VertexType>& verticesBorderSecondary,
        const std::set<DataStructures::VertexType>& verticesBagConnectingSecondary) const
{
    ColourAssignmentV2 mergedColouring{std::get<0>(primaryEntry), std::get<0>(secondaryEntry)};
    SolverV2::HappyVertexAssignmentV2 mergedHappiness{std::get<1>(primaryEntry)};

    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!std::get<0>(primaryEntry).isColoured(vertex) && std::get<0>(secondaryEntry).isColoured(vertex))
        {
            mergedHappiness.setHappiness(vertex, std::get<1>(secondaryEntry).getHappiness(vertex));
        }
    }

    for (DataStructures::VertexType vertex : verticesBorderSecondary)
    {
        if (std::all_of(
                graph->getNeighbours(vertex).begin(),
                graph->getNeighbours(vertex).end(),
                [mergedColouring, vertex](DataStructures::VertexType neighbour)
                {
                    return mergedColouring.getColour(vertex) == mergedColouring.getColour(neighbour);
                }))
        {
            mergedHappiness.setHappiness(vertex, HappinessValue::happy);
        }
        else
        {
            mergedHappiness.setHappiness(vertex, HappinessValue::unhappy);
        }
    }

    for (DataStructures::VertexType vertex : verticesBagConnectingSecondary)
    {
        if (std::get<1>(primaryEntry).getHappiness(vertex) == HappinessValue::happy || std::get<1>(primaryEntry).getHappiness(vertex) == HappinessValue::potentiallyUnhappy)
        {
            if (std::any_of(
                    graph->getNeighbours(vertex).begin(),
                    graph->getNeighbours(vertex).end(),
                    [mergedColouring, vertex](DataStructures::VertexType neighbour)
                    {
                        return mergedColouring.isColoured(neighbour) && mergedColouring.getColour(neighbour) != mergedColouring.getColour(vertex);
                    }))
            {
                mergedHappiness.setHappiness(vertex, HappinessValue::unhappy);
            }
        }
    }

    // Add colouring
    ranking.push(mergedColouring, mergedHappiness, getEvaluation(mergedHappiness));
}


void SolverV2::HeuristicMHVSolverV2::merge( // TODO
        SolverV2::HeuristicSolverRankingV2& ranking,
        const std::shared_ptr<DataStructures::JoinNode>& node,
        const std::shared_ptr<DataStructures::Graph>& graph,
        const SolverV2::HeuristicSolverRankingV2::Entry& primaryEntry,
        const SolverV2::HeuristicSolverRankingV2::Entry& secondaryEntry,
        const std::set<DataStructures::VertexType>& verticesBorder,
        const std::set<DataStructures::VertexType>& verticesBorderPrimary,
        const std::set<DataStructures::VertexType>& verticesBorderSecondary) const
{

    // Split the vertices in the bag in three categories, based on equal colour and equal happiness
    std::set<DataStructures::VertexType> verticesEqual{}; // TODO can be queue's?
    std::set<DataStructures::VertexType> verticesDifferentColour{};
    std::set<DataStructures::VertexType> verticesDifferentHappiness{};
    for (DataStructures::VertexType vertex : node->getBagContent())
    {
        if (std::get<0>(primaryEntry).getColour(vertex) == std::get<0>(secondaryEntry).getColour(vertex))
        {
            if (std::get<1>(primaryEntry).getHappiness(vertex) == std::get<1>(secondaryEntry).getHappiness(vertex))
            {
                verticesEqual.insert(vertex);
            }
            else
            {
                verticesDifferentHappiness.insert(vertex);
            }
        }
        else
        {
            verticesDifferentColour.insert(vertex);
        }
    }

    // Create a merged happiness and colouring
    ColourAssignmentV2 mergedColouring{std::get<0>(primaryEntry), std::get<0>(secondaryEntry)};
    HappyVertexAssignmentV2 mergedHappiness{std::get<1>(primaryEntry)};
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!mergedColouring.isColoured(vertex))
        {
            // Remove the happiness from the vertices in the border
            mergedHappiness.setHappiness(vertex, HappinessValue::unknown);
        }
        else if (!std::get<0>(primaryEntry).isColoured(vertex) && std::get<0>(secondaryEntry).isColoured(vertex))
        {
            // Copy the happiness of the vertices coloured in the secondary entry but not in the first
            mergedHappiness.setHappiness(vertex, std::get<1>(secondaryEntry).getHappiness(vertex));
        }
        else if (std::get<0>(primaryEntry).isColoured(vertex) && std::get<0>(secondaryEntry).isColoured(vertex))
        {
            // Remove all information in the bag from the merged colouring and happiness assignment
            mergedColouring.removeColour(vertex);
            mergedHappiness.setHappiness(vertex, HappinessValue::unknown);
        }
    }

    // A map for the vertices in the border that could be potentially happy, if they are given the corresponding colour
    std::map<DataStructures::VertexType, DataStructures::ColourType> potentialHappyNeighbours{};
    // Keep track of the vertices that you assign a colour but no happiness
    std::queue<DataStructures::VertexType> colouredVerticesWithoutHappiness{};

    // Iterate over all the vertices that have the same happiness and the same colour
    for (DataStructures::VertexType vertex : verticesEqual)
    {
        // Set the colour and happiness of the vertex
        mergedColouring.setColour(vertex, std::get<0>(primaryEntry).getColour(vertex));
        mergedHappiness.setHappiness(vertex, std::get<1>(primaryEntry).getHappiness(vertex));

        if (mergedHappiness.getHappiness(vertex) == HappinessValue::happy)
        {
            colourNeighboursWithSameColour(graph, primaryEntry, secondaryEntry, vertex, mergedColouring, mergedHappiness, potentialHappyNeighbours, colouredVerticesWithoutHappiness);
        }
    }

    // Colour all the vertices which have an equal colour but different happiness
    for (DataStructures::VertexType vertex : verticesDifferentHappiness)
    {
        mergedColouring.setColour(vertex, std::get<0>(primaryEntry).getColour(vertex));
        bool vertexCanBeHappy = std::all_of(
                graph->getNeighbours(vertex).begin(),
                graph->getNeighbours(vertex).end(),
                [mergedColouring, vertex](DataStructures::VertexType neighbour)
                {
                   return !mergedColouring.isColoured(neighbour) || mergedColouring.getColour(neighbour) == mergedColouring.getColour(vertex);
                });
        if (vertexCanBeHappy)
        {
            // Make the vertex happy and colour the neighbours in the same colour
            mergedHappiness.setHappiness(vertex, HappinessValue::happy);
            colourNeighboursWithSameColour(graph, primaryEntry, secondaryEntry, vertex, mergedColouring, mergedHappiness, potentialHappyNeighbours, colouredVerticesWithoutHappiness);
        }
        else
        {
            mergedHappiness.setHappiness(vertex, HappinessValue::unhappy);
        }
    }

    // Colour the vertices from the bag that have been coloured in the previous steps to assure the happiness of some vertices
    while (!colouredVerticesWithoutHappiness.empty())
    {
        DataStructures::VertexType vertex = colouredVerticesWithoutHappiness.front();
        colouredVerticesWithoutHappiness.pop();

        if (mergedHappiness.getHappiness(vertex) != HappinessValue::unknown) continue;

        for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
        {
            if (mergedHappiness.getHappiness(neighbour) == HappinessValue::happy && mergedColouring.getColour(vertex) != mergedColouring.getColour(neighbour))
            {
                mergedHappiness.setHappiness(neighbour, HappinessValue::unhappy);
            }
        }

        if (std::all_of( // TODO maybe you can keep this information during previous stages?
                graph->getNeighbours(vertex).begin(),
                graph->getNeighbours(vertex).end(),
                [vertex, mergedColouring](DataStructures::VertexType neighbour)
                {
                    return !mergedColouring.isColoured(neighbour) || mergedColouring.getColour(vertex) == mergedColouring.getColour(neighbour);
                }))
        {
            mergedHappiness.setHappiness(vertex, HappinessValue::happy);
            colourNeighboursWithSameColour(graph, primaryEntry, secondaryEntry, vertex, mergedColouring, mergedHappiness, potentialHappyNeighbours, colouredVerticesWithoutHappiness);
        }
        else
        {
            mergedHappiness.setHappiness(vertex, HappinessValue::unhappy);
        }
    }


    while (std::any_of(
            verticesDifferentColour.begin(),
            verticesDifferentColour.end(),
            [mergedHappiness](DataStructures::VertexType vertex){ return mergedHappiness.getHappiness(vertex) == HappinessValue::unknown; } ))
    {
        DataStructures::VertexType vertexToColour = *std::find_if(
                verticesDifferentColour.begin(),
                verticesDifferentColour.end(),
                [mergedColouring](DataStructures::VertexType vertex){ return !mergedColouring.isColoured(vertex); });

        std::uniform_real_distribution<> dist(0, 1);
        if (dist(RNG::rng) < 0.5)
        {
            mergedColouring.setColour(vertexToColour, std::get<0>(primaryEntry).getColour(vertexToColour));
        }
        else
        {
            mergedColouring.setColour(vertexToColour, std::get<0>(secondaryEntry).getColour(vertexToColour));
        }

        colouredVerticesWithoutHappiness.push(vertexToColour);

        while (!colouredVerticesWithoutHappiness.empty())
        {
            DataStructures::VertexType vertex = colouredVerticesWithoutHappiness.front();
            colouredVerticesWithoutHappiness.pop();

            if (mergedHappiness.getHappiness(vertex) != HappinessValue::unknown) continue;

            for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
            {
                if (mergedHappiness.getHappiness(neighbour) == HappinessValue::happy && mergedColouring.getColour(vertex) != mergedColouring.getColour(neighbour))
                {
                    mergedHappiness.setHappiness(neighbour, HappinessValue::unhappy);
                }
            }

            if (std::all_of( // TODO maybe you can keep this information during previous stages?
            graph->getNeighbours(vertex).begin(),
            graph->getNeighbours(vertex).end(),
            [vertex, mergedColouring](DataStructures::VertexType neighbour)
            {
                return !mergedColouring.isColoured(neighbour) || mergedColouring.getColour(vertex) == mergedColouring.getColour(neighbour);
            }))
            {
                mergedHappiness.setHappiness(vertex, HappinessValue::happy);
                colourNeighboursWithSameColour(graph, primaryEntry, secondaryEntry, vertex, mergedColouring, mergedHappiness, potentialHappyNeighbours, colouredVerticesWithoutHappiness);
            }
            else
            {
                mergedHappiness.setHappiness(vertex, HappinessValue::unhappy);
            }
        }
    }

    for (const auto& [potentiallyHappyVertex, colourPotentiallyHappyNeighbour] : potentialHappyNeighbours)
    {
        mergedHappiness.setHappiness(potentiallyHappyVertex, HappinessValue::potentiallyHappy);
    }

    ranking.push(mergedColouring, mergedHappiness, getEvaluation(mergedHappiness));
}


void SolverV2::HeuristicMHVSolverV2::colourNeighboursWithSameColour( // TODO
        const std::shared_ptr<DataStructures::Graph>& graph,
        const SolverV2::HeuristicSolverRankingV2::Entry& primaryEntry,
        const SolverV2::HeuristicSolverRankingV2::Entry& secondaryEntry,
        DataStructures::VertexType vertex,
        SolverV2::ColourAssignmentV2& mergedColouring,
        SolverV2::HappyVertexAssignmentV2& mergedHappiness,
        std::map<DataStructures::VertexType, DataStructures::ColourType>& potentialHappyNeighbours,
        std::queue<DataStructures::VertexType>& colouredVerticesWithoutHappiness)
{
    for (DataStructures::VertexType neighbour : graph->getNeighbours(vertex))
    {
        if (mergedColouring.isColoured(neighbour))
        {
            if (mergedHappiness.getHappiness(neighbour) == HappinessValue::happy &&
                (!std::get<0>(primaryEntry).isColoured(neighbour) || !std::get<0>(primaryEntry).isColoured(neighbour)))
            {
                mergedHappiness.setHappiness(neighbour, HappinessValue::unhappy);
            }
        }
        else
        {
            if (std::get<0>(primaryEntry).isColoured(neighbour) && std::get<0>(secondaryEntry).isColoured(neighbour))
            {
                mergedColouring.setColour(neighbour, mergedColouring.getColour(vertex));
                colouredVerticesWithoutHappiness.push(neighbour);
            }
            else if (!std::get<0>(primaryEntry).isColoured(neighbour) && !std::get<0>(secondaryEntry).isColoured(neighbour))
            {
                // Skip vertices that are already known to be unhappy
                if (mergedHappiness.getHappiness(neighbour) == HappinessValue::unhappy) continue;

                if (graph->isPrecoloured(neighbour))
                {
                    // If the neighbour is precoloured, then it can only become happy if the vertex is coloured in that colour
                    if (mergedColouring.getColour(vertex) != graph->getColour(neighbour))
                    {
                        mergedHappiness.setHappiness(neighbour, HappinessValue::unhappy);
                    }
                    else
                    {
                        potentialHappyNeighbours.insert(std::make_pair(neighbour, mergedColouring.getColour(vertex)));
                    }
                }
                else
                {
                    // Otherwise, the vertex could be potentially happy if it receives the same colour as the vertex
                    auto insertResult = potentialHappyNeighbours.insert(std::make_pair(neighbour, mergedColouring.getColour(vertex)));
                    if (insertResult.first->second != mergedColouring.getColour(vertex))
                    {
                        // If the vertex already exists with another colour, then it will be unhappy
                        potentialHappyNeighbours.erase(insertResult.first);
                        mergedHappiness.setHappiness(neighbour, HappinessValue::unhappy);
                    }
                }
            }
        }
    }
}
