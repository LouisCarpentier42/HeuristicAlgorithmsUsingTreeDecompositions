//
// Created by louis on 10/11/2021.
//

#include "HeuristicTreeDecompositionSolver.h"

#include <algorithm>

const int NB_SOLUTIONS_TO_KEEP{16}; // TODO make more generic

MaximumHappyVertices::HeuristicTreeDecompositionSolver::HeuristicTreeDecompositionSolver(
        const DataStructures::Graph& graph,
        const DataStructures::Colouring& partialColouring,
        const DataStructures::NiceTreeDecomposition& treeDecomposition)
    : MaximumHappyVerticesSolver(graph, partialColouring), treeDecomposition{treeDecomposition}
{}

DataStructures::MutableColouring* MaximumHappyVertices::HeuristicTreeDecompositionSolver::solve() const
{
    DataStructures::ColouringQueue rootColourings = solveAtBag(treeDecomposition.getRoot());
    std::cout << "[MY ALGO] Nb happy vertices: " << evaluator.evaluate(rootColourings.retrieveBestColouring()) << "\n"; // TODO remove
    return rootColourings.retrieveBestColouring();
}

DataStructures::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::solveAtBag(const DataStructures::NiceBag* bag) const
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

DataStructures::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleLeafBag(const DataStructures::LeafBag* bag) const
{
    std::cout << "--- b(" << bag->getId() << "): leaf \n";
    DataStructures::ColouringQueue initialColouringQueue = createEmptyColouringQueue();
    initialColouringQueue.push(new DataStructures::MutableColouring{colouring});
    return initialColouringQueue;
}

DataStructures::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleIntroduceVertexBag(const DataStructures::IntroduceVertexBag* bag) const
{
    DataStructures::ColouringQueue childColourings = solveAtBag(bag->getChild());
    DataStructures::VertexType introducedVertex{bag->getIntroducedVertex()};
    std::cout << "--- b(" << bag->getId() << "): introduce " << introducedVertex << "\n";

    // Precoloured vertices may not receive a new colour
    if (colouring.isColoured(introducedVertex)) return childColourings;

    DataStructures::ColouringQueue newColourings = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* childColouring : childColourings)
    {
        for (DataStructures::ColourType colour{1}; colour <= colouring.getNbColours(); colour++)
        {
            auto* newColouring = new DataStructures::MutableColouring{*childColouring};
            newColouring->setColour(introducedVertex, colour);
            std::vector<DataStructures::MutableColouring*> currentColourings;
            newColourings.push(newColouring);
        }
    }
    return newColourings;
}

DataStructures::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleForgetVertexBag(const DataStructures::ForgetVertexBag* bag) const
{
    return solveAtBag(bag->getChild());
}

DataStructures::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::handleJoinBag(const DataStructures::JoinBag* bag) const
{
    DataStructures::ColouringQueue leftChildSolutions = solveAtBag(bag->getLeftChild());
    DataStructures::ColouringQueue rightChildSolutions = solveAtBag(bag->getRightChild());
    std::cout << "--- b(" << bag->getId() << "): join b(" << bag->getLeftChild()->getId() << ") and b(" << bag->getRightChild()->getId() << ")\n";

    DataStructures::ColouringQueue newSolutions = createEmptyColouringQueue();
    for (DataStructures::MutableColouring* leftColouring : leftChildSolutions)
    {
        for (DataStructures::MutableColouring* rightColouring : rightChildSolutions)
        {
            auto* newColouring = new DataStructures::MutableColouring{colouring};
            // TODO, if the left colouring and right colouring differ too much, skip them
            for (DataStructures::VertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
            {
                if (colouring.isColoured(vertex)) continue; // Skip precoloured vertices
                if (leftColouring->isColoured(vertex) && rightColouring->isColoured(vertex))
                {
                    newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    int leftNbHappyVertices{evaluator.evaluate(newColouring)};
                    newColouring->setColour(vertex, rightColouring->getColour(vertex));
                    int rightNbHappyVertices{evaluator.evaluate(newColouring)};

                    if (leftNbHappyVertices > rightNbHappyVertices) // TODO probably can be done with evaluator(left, right)
                    {
                        newColouring->setColour(vertex, leftColouring->getColour(vertex));
                    }
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
            newSolutions.push(newColouring);
        }
    }
    return newSolutions;
}

DataStructures::ColouringQueue MaximumHappyVertices::HeuristicTreeDecompositionSolver::createEmptyColouringQueue() const
{
    return DataStructures::ColouringQueue{NB_SOLUTIONS_TO_KEEP, evaluator};
}
