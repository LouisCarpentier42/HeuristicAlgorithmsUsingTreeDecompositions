//
// Created by louis on 10/11/2021.
//

#include "HeuristicTreeDecompositionSolver.h"

#include <algorithm>
#include <unordered_set>

const int NB_SOLUTIONS_TO_KEEP{15}; // TODO make more generic

const int VERTEX{12};

MaximumHappyVertices::HeuristicTreeDecompositionSolver::HeuristicTreeDecompositionSolver(
        const DataStructures::Graph& graph,
        const DataStructures::PartialColouring& partialColouring,
        const DataStructures::NiceTreeDecomposition& treeDecomposition)
        : MaximumHappyVerticesSolver(graph, partialColouring), treeDecomposition{treeDecomposition}
{}

DataStructures::Colouring* MaximumHappyVertices::HeuristicTreeDecompositionSolver::solve() const
{
    std::vector<DataStructures::Colouring*> solutions = solveAtBag(treeDecomposition.getRoot());
    DataStructures::Colouring* bestColouring{nullptr};
    unsigned int maxNbHappyVertices{0};
    for (DataStructures::Colouring* solution : solutions)
    {
        unsigned int nbHappyVertices{getNbHappyVertices(solution)};
        if (nbHappyVertices > maxNbHappyVertices)
        {
            bestColouring = solution;
            maxNbHappyVertices = nbHappyVertices;
        }
    }
    std::cout << "[MY ALGO] Nb happy vertices: " << maxNbHappyVertices << "\n"; // TODO remove
    return bestColouring;
}

std::vector<DataStructures::Colouring*> MaximumHappyVertices::HeuristicTreeDecompositionSolver::solveAtBag(const DataStructures::NiceBag* bag) const
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

std::vector<DataStructures::Colouring*> MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleLeafBag(const DataStructures::LeafBag* bag) const
{
    return std::vector<DataStructures::Colouring*>{new DataStructures::Colouring{partialColouring}};
}

std::vector<DataStructures::Colouring*> MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag* bag) const
{
    std::vector<DataStructures::Colouring*> childSolutions = solveAtBag(bag->getChild());
    DataStructures::VertexType introducedVertex{bag->getIntroducedVertex()};

    if (partialColouring.isColoured(introducedVertex))
    {
        return childSolutions;
    }

    // TODO optimize: keep track of evaluation of NB_SOLUTIONS_TO_KEEPth worst solutions and only add if it is nb happy vertices is larger
    std::vector<DataStructures::Colouring*> allSolutions{};
    for (DataStructures::Colouring* childColouring : childSolutions)
    {
        bool hasBeenColoured{false};
        for (DataStructures::VertexType neighbour : *graph.getNeighbours(introducedVertex))
        {
            if (childColouring->isColoured(neighbour))
            {
                hasBeenColoured = true;
                auto* newColouring = new DataStructures::Colouring{*childColouring};
                newColouring->setColour(introducedVertex, childColouring->getColour(neighbour));
                allSolutions.push_back(newColouring);
            }
        }
        // If none of the neighbours is coloured, add all possible colours
        if (!hasBeenColoured)
        {
            for (DataStructures::ColourType colour{1}; colour <= partialColouring.getNbColours(); colour++)
            {
                auto* newColouring = new DataStructures::Colouring{*childColouring};
                newColouring->setColour(introducedVertex, colour);
                allSolutions.push_back(newColouring);
            }
        }
    }

    if (allSolutions.size() <= NB_SOLUTIONS_TO_KEEP)
        return allSolutions;

    // TODO probably a memory leak with the pruned colourings
    std::vector<DataStructures::Colouring*> prunedSolutions(NB_SOLUTIONS_TO_KEEP);
    std::partial_sort_copy(allSolutions.begin(), allSolutions.end(),
                           prunedSolutions.begin(), prunedSolutions.end(),
                           [this] (DataStructures::Colouring* const c1, DataStructures::Colouring* const c2)
                           { return getNbHappyVertices(c1) > getNbHappyVertices(c2);
                       });

    return prunedSolutions;
}

std::vector<DataStructures::Colouring*> MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const
{
    return solveAtBag(bag->getChild());
}

std::vector<DataStructures::Colouring*> MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleJoinBag(const DataStructures::JoinBag* bag) const
{
    std::vector<DataStructures::Colouring*> leftChildSolutions = solveAtBag(bag->getLeftChild());
    std::vector<DataStructures::Colouring*> rightChildSolutions = solveAtBag(bag->getRightChild());

    std::vector<DataStructures::Colouring*> allSolutions{};
    for (DataStructures::Colouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::Colouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::Colouring{partialColouring};
            allSolutions.push_back(newColouring);
            for (DataStructures::VertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
            {
                if (partialColouring.isColoured(vertex)) continue;
                if (leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    unsigned int leftNbHappyVertices{getNbHappyVertices(newColouring)};
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
                    unsigned int rightNbHappyVertices{getNbHappyVertices(newColouring)};

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
        }
    }

    if (allSolutions.size() <= NB_SOLUTIONS_TO_KEEP)
        return allSolutions;

    // TODO probably a memory leak with the pruned colourings
    std::vector<DataStructures::Colouring*> prunedSolutions(NB_SOLUTIONS_TO_KEEP);
    std::partial_sort_copy(allSolutions.begin(), allSolutions.end(),
                           prunedSolutions.begin(), prunedSolutions.end(),
                           [this] (DataStructures::Colouring* const c1, DataStructures::Colouring* const c2)
                           { return getNbHappyVertices(c1) > getNbHappyVertices(c2);
                           });

    return prunedSolutions;
}
