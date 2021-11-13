//
// Created by louis on 10/11/2021.
//

#include "HeuristicTreeDecompositionSolver.h"

#include <algorithm>

const int NB_SOLUTIONS_TO_KEEP{16}; // TODO make more generic

MaximumHappyVertices::HeuristicTreeDecompositionSolver::HeuristicTreeDecompositionSolver(
        const DataStructures::Graph& graph,
        const DataStructures::PartialColouring& partialColouring,
        const DataStructures::NiceTreeDecomposition& treeDecomposition)
        : MaximumHappyVerticesSolver(graph, partialColouring), treeDecomposition{treeDecomposition}
{}

DataStructures::Colouring* MaximumHappyVertices::HeuristicTreeDecompositionSolver::solve() const
{
    ColouringQueue rootColourings = solveAtBag(treeDecomposition.getRoot());
    while (rootColourings.size() > 1)
    {
        delete rootColourings.top();
        rootColourings.pop();
    }
    std::cout << "[MY ALGO] Nb happy vertices: " << graph.getNbHappyVertices(rootColourings.top()) << "\n"; // TODO remove
    return rootColourings.top();
}

MaximumHappyVertices::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::solveAtBag(const DataStructures::NiceBag* bag) const
{
    switch(bag->getBagType())
    {
        case DataStructures::BagType::LeafBag:
            return handleLeafBag(dynamic_cast<const DataStructures::LeafBag*>(bag));
        case DataStructures::BagType::IntroduceVertexBag:
            return handleIntroduceVertexBag(dynamic_cast<const DataStructures::IntroduceVertexBag*>(bag));
        case DataStructures::BagType::ForgetVertexBag:
            return handleForgetVertexBag(dynamic_cast<const DataStructures::ForgetVertexBag*>(bag));
        case DataStructures::BagType::JoinBag:
            return handleJoinBag(dynamic_cast<const DataStructures::JoinBag*>(bag));
    }
}

MaximumHappyVertices::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleLeafBag(const DataStructures::LeafBag* bag) const
{
    ColouringQueue initialColouringQueue = createEmptyColouringQueue();
    initialColouringQueue.push(new DataStructures::Colouring{partialColouring});
    return initialColouringQueue;
}

MaximumHappyVertices::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag* bag) const
{
    ColouringQueue childColourings = solveAtBag(bag->getChild());
    DataStructures::VertexType introducedVertex{bag->getIntroducedVertex()};

    // Precoloured vertices may not receive a new colour
    if (partialColouring.isColoured(introducedVertex)) return childColourings;

    ColouringQueue newColourings = createEmptyColouringQueue();
    while (!childColourings.empty())
    {
        DataStructures::Colouring* childColouring = childColourings.top();
        bool hasBeenColoured{false};
        for (DataStructures::VertexType neighbour : *graph.getNeighbours(introducedVertex))
        {
            if (childColouring->isColoured(neighbour))
            {
                hasBeenColoured = true;
                auto* newColouring = new DataStructures::Colouring{*childColouring};
                newColouring->setColour(introducedVertex, childColouring->getColour(neighbour));
                newColourings.push(newColouring);
            }
        }
        // If none of the neighbours is coloured, add all possible colours
        if (!hasBeenColoured)
        {
            for (DataStructures::ColourType colour{1}; colour <= partialColouring.getNbColours(); colour++)
            {
                auto* newColouring = new DataStructures::Colouring{*childColouring};
                newColouring->setColour(introducedVertex, colour);
                newColourings.push(newColouring);
            }
        }
        while (newColourings.size() > NB_SOLUTIONS_TO_KEEP)
        {
            delete newColourings.top();
            newColourings.pop();
        }
        childColourings.pop();
    }

    return newColourings;

//    std::vector<DataStructures::Colouring*> allSolutions{};
//    for (DataStructures::Colouring* childColouring : childSolutions)
//    {
//        bool hasBeenColoured{false};
//        for (DataStructures::VertexType neighbour : *graph.getNeighbours(introducedVertex))
//        {
//            if (childColouring->isColoured(neighbour))
//            {
//                hasBeenColoured = true;
//                auto* newColouring = new DataStructures::Colouring{*childColouring};
//                newColouring->setColour(introducedVertex, childColouring->getColour(neighbour));
//                allSolutions.push_back(newColouring);
//            }
//        }
//        // If none of the neighbours is coloured, add all possible colours
//        if (!hasBeenColoured)
//        {
//            for (DataStructures::ColourType colour{1}; colour <= partialColouring.getNbColours(); colour++)
//            {
//                auto* newColouring = new DataStructures::Colouring{*childColouring};
//                newColouring->setColour(introducedVertex, colour);
//                allSolutions.push_back(newColouring);
//            }
//        }
//    }
//
//    if (allSolutions.size() <= NB_SOLUTIONS_TO_KEEP)
//        return allSolutions;
//
//    // TODO probably a memory leak with the pruned colourings
//    std::vector<DataStructures::Colouring*> prunedSolutions(NB_SOLUTIONS_TO_KEEP);
//    std::partial_sort_copy(allSolutions.begin(), allSolutions.end(),
//                           prunedSolutions.begin(), prunedSolutions.end(),
//                           [this] (DataStructures::Colouring* const c1, DataStructures::Colouring* const c2)
//                           { return graph.getNbHappyVertices(c1) > graph.getNbHappyVertices(c2); });
//
//    return prunedSolutions;
}

MaximumHappyVertices::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const
{
    return solveAtBag(bag->getChild());
}

MaximumHappyVertices::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleJoinBag(const DataStructures::JoinBag* bag) const
{
    ColouringQueue leftChildSolutions = solveAtBag(bag->getLeftChild());
    ColouringQueue rightChildSolutions = solveAtBag(bag->getRightChild());

    std::vector<DataStructures::Colouring*> rightChildVector{};
    while(!rightChildSolutions.empty())
    {
        rightChildVector.emplace_back(rightChildSolutions.top());
        rightChildSolutions.pop();
    }

    ColouringQueue newSolutions = createEmptyColouringQueue();
    while (!leftChildSolutions.empty())
    {
        DataStructures::Colouring* leftColouring = leftChildSolutions.top();
        for (DataStructures::Colouring* rightColouring : rightChildVector)
        {
            auto* newColouring = new DataStructures::Colouring{partialColouring};
            newSolutions.push(newColouring);
            for (DataStructures::VertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
            {
                if (partialColouring.isColoured(vertex)) continue;
                if (leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    unsigned int leftNbHappyVertices{graph.getNbHappyVertices(newColouring)};
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
                    unsigned int rightNbHappyVertices{graph.getNbHappyVertices(newColouring)};

                    if (leftNbHappyVertices > rightNbHappyVertices)
                    {
                        newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    }
                    // If right has better result, then this is already ok because newColouring has vertex set to rightColour
                    // TODO If both are equally good, select random or add both
                }
                else if (leftColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                }
                else if (rightColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
                }
            }
            if (newSolutions.size() > NB_SOLUTIONS_TO_KEEP)
                newSolutions.pop();
        }
        delete leftColouring;
        leftChildSolutions.pop();
    }

    for (DataStructures::Colouring* colouring : rightChildVector)
        delete colouring;

    return newSolutions;

//    std::vector<DataStructures::Colouring*> allSolutions{};
//    for (DataStructures::Colouring* leftColouring : leftChildSolutions)
//    {
//        for (DataStructures::Colouring* rightColouring : rightChildSolutions)
//        {
//            auto* newColouring = new DataStructures::Colouring{partialColouring};
//            allSolutions.push_back(newColouring);
//            for (DataStructures::VertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
//            {
//                if (partialColouring.isColoured(vertex)) continue;
//                if (leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
//                {
//                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
//                    unsigned int leftNbHappyVertices{graph.getNbHappyVertices(newColouring)};
//                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
//                    unsigned int rightNbHappyVertices{graph.getNbHappyVertices(newColouring)};
//
//                    if (leftNbHappyVertices > rightNbHappyVertices)
//                    {
//                        newColouring->setColour(vertex, leftColouring->getColour(vertex));
//                    }
//                    // If right has better result, then this is already ok because newColouring has vertex set to rightColour
//                    // TODO If both are equally good, select random or add both
//                }
//                else if (leftColouring->isColoured(vertex))
//                {
//                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
//                }
//                else if (rightColouring->isColoured(vertex))
//                {
//                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
//                }
//            }
//        }
//    }
//
//    if (allSolutions.size() <= NB_SOLUTIONS_TO_KEEP)
//        return allSolutions;
//
//    // TODO probably a memory leak with the pruned colourings
//    std::vector<DataStructures::Colouring*> prunedSolutions(NB_SOLUTIONS_TO_KEEP);
//    std::partial_sort_copy(allSolutions.begin(), allSolutions.end(),
//                           prunedSolutions.begin(), prunedSolutions.end(),
//                           [this] (DataStructures::Colouring* const c1, DataStructures::Colouring* const c2)
//                           { return graph.getNbHappyVertices(c1) > graph.getNbHappyVertices(c2);
//                           });
//
//    return prunedSolutions;
}

MaximumHappyVertices::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::createEmptyColouringQueue() const
{
    return MaximumHappyVertices::ColouringQueue(Comparator(graph));
}
