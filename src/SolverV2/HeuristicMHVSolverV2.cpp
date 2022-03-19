//
// Created by louis on 17/03/2022.
//

#include <algorithm>
#include "HeuristicMHVSolverV2.h"


SolverV2::HeuristicMHVSolverV2::HeuristicMHVSolverV2(int nbSolutionsToKeep) : nbSolutionsToKeep(nbSolutionsToKeep) {}

int SolverV2::HeuristicMHVSolverV2::solve(
        std::shared_ptr<DataStructures::Graph>& graph,
        std::shared_ptr<DataStructures::NiceTreeDecomposition>& treeDecomposition) const
{
    // Create S
    std::set<DataStructures::VertexType> S{};
    std::vector<bool> coloursUsed(graph->getNbColours()+1, false);
    std::cout << "S: ";
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (graph->isPrecoloured(vertex) && !coloursUsed[graph->getColour(vertex)])
        {
            coloursUsed[graph->getColour(vertex)] = true;
            S.insert(vertex);
            std::cout << vertex << ", ";
        }
    }
    std::cout << "\n";

    std::cout << "Precoloured vertices: ";
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (graph->isPrecoloured(vertex))
            std::cout << vertex << ", ";
    }
    std::cout << "\n";

    HeuristicSolverRankingV2 ranking = solveAtNode(treeDecomposition->getRoot(), graph, S);
    std::cout << "FINAL RANKING\n";
    std::cout << ranking << "\n";
    if (ranking.size() > 0)
    {
        HeuristicSolverRankingV2::Entry bestEntry = ranking.getBestEntry();

        // Colour graph
        for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        {
            if (!graph->isPrecoloured(vertex))
                graph->setColour(vertex, std::get<0>(bestEntry)->getColour(vertex));
        }

        return std::get<2>(bestEntry);
    }
    else
    {
        std::cout << "No viable solution found\n";
        return 0;
    }
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::solveAtNode(
        const std::shared_ptr<DataStructures::NiceNode>& node,
        std::shared_ptr<DataStructures::Graph>& graph,
        std::set<DataStructures::VertexType>& S) const
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
//    // !!! The happy vertices are only correctly set for those vertices handled in the bag !!!
//    switch(node->getNodeType())
//    {
//        case DataStructures::NodeType::LeafNode:
//        {
//            auto ranking = handleLeafNode(std::dynamic_pointer_cast<DataStructures::LeafNode>(node), graph, S);
//            for (HeuristicSolverRankingV2::Entry& entry : ranking)
//            {
//                int nbVerticesHappy{0};
//                for (auto v{0}; v < graph->getNbVertices(); v++)
//                {
//                    if (std::get<1>(entry).isHappy(v)) nbVerticesHappy++;
//                }
//                if (nbVerticesHappy != std::get<2>(entry))
//                {
//                    std::cout << "Problem in Leaf node " << node->getId() << ": " << entry;
//                }
//            }
//            return ranking;
//        }
//        case DataStructures::NodeType::IntroduceNode:
//        {
//            auto ranking = handleIntroduceNode(std::dynamic_pointer_cast<DataStructures::IntroduceNode>(node), graph, S);
//            for (HeuristicSolverRankingV2::Entry& entry : ranking)
//            {
//                int nbVerticesHappy{0};
//                for (auto v{0}; v < graph->getNbVertices(); v++)
//                {
//                    if (std::get<1>(entry).isHappy(v)) nbVerticesHappy++;
//                }
//                if (nbVerticesHappy != std::get<2>(entry))
//                {
//                    std::cout << "Problem in Introduce node " << node->getId() << ": " << entry;
//                }
//            }
//            return ranking;
//        }
//        case DataStructures::NodeType::ForgetNode:
//        {
//            auto ranking = handleForgetNode(std::dynamic_pointer_cast<DataStructures::ForgetNode>(node), graph, S);
//            for (HeuristicSolverRankingV2::Entry& entry : ranking)
//            {
//                int nbVerticesHappy{0};
//                for (auto v{0}; v < graph->getNbVertices(); v++)
//                {
//                    if (std::get<1>(entry).isHappy(v)) nbVerticesHappy++;
//                }
//                if (nbVerticesHappy != std::get<2>(entry))
//                {
//                    std::cout << "Problem in Forget node " << node->getId() << ": " << entry;
//                }
//            }
//            return ranking;
//        }
//        case DataStructures::NodeType::JoinNode:
//        {
//            auto ranking = handleJoinNode(std::dynamic_pointer_cast<DataStructures::JoinNode>(node), graph, S);
//            for (HeuristicSolverRankingV2::Entry& entry : ranking)
//            {
//                int nbVerticesHappy{0};
//                for (auto v{0}; v < graph->getNbVertices(); v++)
//                {
//                    if (std::get<1>(entry).isHappy(v)) nbVerticesHappy++;
//                }
//                if (nbVerticesHappy != std::get<2>(entry))
//                {
//                    std::cout << "Problem in Join node " << node->getId() << ": " << entry;
//                }
//            }
//            return ranking;
//        }
//    }
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleLeafNode(
        const std::shared_ptr<DataStructures::LeafNode>& node,
        std::shared_ptr<DataStructures::Graph>& graph,
        std::set<DataStructures::VertexType>& S) const
{
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};

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
            happyVertices.insert(vertex);
    }

    // Create an assignment in which all the vertices that can be happy are happy
    // This assignment will be used to create assignments in which vertices are not happy
    DataStructures::HappyVerticesAssignments allVerticesHappy{graph};
    for (DataStructures::VertexType vertex : happyVertices)
        allVerticesHappy.makeHappy(vertex);

    // Add assignment in which all vertices are assigned happy
    auto allHappyColourAssignments = std::make_shared<DataStructures::ColourAssignment>(graph);
    for (DataStructures::VertexType vertexInS : S)
        allHappyColourAssignments->assignColour(vertexInS, graph->getColour(vertexInS));
    DataStructures::HappyVerticesAssignments allHappyHappyVerticesAssignments{allVerticesHappy};
    ranking.push(allHappyColourAssignments, allHappyHappyVerticesAssignments, happyVertices.size());

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
            auto colourAssignments = std::make_shared<DataStructures::ColourAssignment>(graph);
            for (DataStructures::VertexType vertexInS : S)
                colourAssignments->assignColour(vertexInS, graph->getColour(vertexInS));
            // Create the happy vertex assignment
            DataStructures::HappyVerticesAssignments happyVerticesAssignments{allVerticesHappy};
            for (DataStructures::VertexType unhappyVertex : unhappyVertices)
                happyVerticesAssignments.makeUnhappy(unhappyVertex);
            // Add the assignment to the ranking
            ranking.push(colourAssignments, happyVerticesAssignments, happyVertices.size() - unhappyVertices.size());
        }

    }

    return ranking;
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleIntroduceNode(
        const std::shared_ptr<DataStructures::IntroduceNode>& node,
        std::shared_ptr<DataStructures::Graph>& graph,
        std::set<DataStructures::VertexType>& S) const
{
    HeuristicSolverRankingV2 rankingChild = solveAtNode(node->getChild(), graph, S);

    if (S.find(node->getIntroducedVertex()) != S.end())
    {
        return rankingChild;
    }

    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};

    for (auto& [colourAssignmentChild, happyVerticesAssignmentsChild, evaluationChild] : rankingChild)
    {
        // TODO can be optimized by gathering the valid colours for assigning happy and unhappy
        for (DataStructures::ColourType colour{1}; colour <= graph->getNbColours(); colour++)
        {
            if (graph->isPrecoloured(node->getIntroducedVertex()) && graph->getColour(node->getIntroducedVertex()) != colour) continue;

            bool allNeighboursSameColour{true};
            bool allHappyNeighboursSameColour{true};
            for (DataStructures::VertexType neighbour : graph->getNeighbours(node->getIntroducedVertex()))
            {
                if (colourAssignmentChild->isColoured(neighbour) && colourAssignmentChild->getColour(neighbour) != colour)
                {
                    allNeighboursSameColour = false;
                    if (happyVerticesAssignmentsChild.isHappy(neighbour))
                    {
                        allHappyNeighboursSameColour = false;
                        break;
                    }
                }
            }

            // If some happy has the same colour, then it wouldn't be happy anymore
            if (!allHappyNeighboursSameColour) continue;

            // Only if all coloured neighbours have the same colour, the vertex can be happy
            if (allNeighboursSameColour)
            {
                auto colourAssignmentHappy = std::make_shared<DataStructures::ColourAssignment>(node, colourAssignmentChild);
                colourAssignmentHappy->assignColour(node->getIntroducedVertex(), colour);
                DataStructures::HappyVerticesAssignments happyVerticesAssignmentsHappy{happyVerticesAssignmentsChild};
                happyVerticesAssignmentsHappy.makeHappy(node->getIntroducedVertex());

                ranking.push(colourAssignmentHappy, happyVerticesAssignmentsHappy, evaluationChild + 1); // TODO slightly more advanced eval
            }

            // Assigning the introduced vertex unhappy can be done without any axuiliary checks
            auto colourAssignmentUnhappy = std::make_shared<DataStructures::ColourAssignment>(node, colourAssignmentChild);
            colourAssignmentUnhappy->assignColour(node->getIntroducedVertex(), colour);
            DataStructures::HappyVerticesAssignments happyVerticesAssignmentsUnhappy{happyVerticesAssignmentsChild};
            happyVerticesAssignmentsUnhappy.makeUnhappy(node->getIntroducedVertex());

            ranking.push(colourAssignmentUnhappy, happyVerticesAssignmentsUnhappy, evaluationChild);
        }

    }

    return ranking;
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleForgetNode(
        const std::shared_ptr<DataStructures::ForgetNode>& node,
        std::shared_ptr<DataStructures::Graph>& graph,
        std::set<DataStructures::VertexType>& S) const
{
    return solveAtNode(node->getChild(), graph, S);
}

SolverV2::HeuristicSolverRankingV2 SolverV2::HeuristicMHVSolverV2::handleJoinNode(
        const std::shared_ptr<DataStructures::JoinNode>& node,
        std::shared_ptr<DataStructures::Graph>& graph,
        std::set<DataStructures::VertexType>& S) const
{
    HeuristicSolverRankingV2 rankingLeftChild = solveAtNode(node->getLeftChild(), graph, S);
    HeuristicSolverRankingV2 rankingRightChild = solveAtNode(node->getRightChild(), graph, S);
    HeuristicSolverRankingV2 ranking{nbSolutionsToKeep};
//
//    std::cout << "Start solving join node " << node->getId() << "\n"; // TODO remove
//    std::cout << "Ranking left child " << node->getLeftChild()->getId() << "\n";
//    std::cout << rankingLeftChild << "\n";
//    std::cout << "Ranking right child " << node->getRightChild()->getId() << "\n";
//    std::cout << rankingRightChild << "\n";

    // Gather all vertices that should be coloured, that is the vertices in S and the vertices in the bag
    std::set<DataStructures::VertexType> verticesToConsider{S};
    for (DataStructures::VertexType vertex : node->getBagContent())
        verticesToConsider.insert(vertex);

//    std::cout << "Vertices to consider: "; // TODO remove
//    for (DataStructures::VertexType vertex : verticesToConsider)
//    {
//        std::cout << vertex << ", ";
//    }
//    std::cout << "\n";


    for (auto& [colourAssignmentLeft, happyVerticesAssignmentsLeft, evaluationLeft] : rankingLeftChild)
    {
        for (auto& [colourAssignmentRight, happyVerticesAssignmentsRight, evaluationRight] : rankingRightChild)
        {
            bool noMistakes{true};
            int nbHappyVerticesCountedDouble{0};
            for (DataStructures::VertexType vertex : verticesToConsider)
            {
                bool sameColour = colourAssignmentLeft->getColourConst(vertex) == colourAssignmentRight->getColourConst(vertex);
                bool sameHappiness = happyVerticesAssignmentsLeft.isHappy(vertex) == happyVerticesAssignmentsRight.isHappy(vertex);
                if (!(sameColour && sameHappiness))
                {
                    noMistakes = false;
                    break;
                }
                if (happyVerticesAssignmentsLeft.isHappy(vertex))
                    nbHappyVerticesCountedDouble++;
            }

            if (noMistakes)
            {
                ranking.push(
                        std::make_shared<DataStructures::ColourAssignment>(node, colourAssignmentLeft, colourAssignmentRight),
                        happyVerticesAssignmentsLeft, // Important information is in bag and S, which is in the child assignments and equal for left and right
                        evaluationLeft + evaluationRight - nbHappyVerticesCountedDouble);
            }
        }
    }

//    std::cout << "Done solving join node " << node->getId() << "\n"; // TODO remove
//    std::cout << ranking << "\n";
    return ranking;
}
