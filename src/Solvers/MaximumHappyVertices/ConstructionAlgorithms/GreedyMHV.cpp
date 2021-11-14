//
// Created by louis on 25/10/2021.
//

#include "GreedyMHV.h"

MaximumHappyVertices::GreedyMHV::GreedyMHV(
        const DataStructures::Graph& graph,
        const DataStructures::Colouring& colouring)
    : MaximumHappyVerticesSolver(graph, colouring)
{}

DataStructures::MutableColouring* MaximumHappyVertices::GreedyMHV::solve() const
{
    // TODO maybe this can be done fully with std::min_element?
    //      -> probably need to change helper function colour all vertices to return the evaluation or a new colouring
    DataStructures::ColourType bestColour{1};
    auto* solution = new DataStructures::MutableColouring{colouring};
    int bestNbHappyVertices{0};

    for (DataStructures::ColourType colour{1}; colour <= colouring.getNbColours(); colour++)
    {
        colourAllVertices(solution, colour);
        int nbHappyVertices{evaluator.evaluate(solution)};
        if (nbHappyVertices > bestNbHappyVertices)
        {
            bestColour = colour;
            bestNbHappyVertices = nbHappyVertices;
        }
    }
    colourAllVertices(solution, bestColour);
    std::cout << "[GREEDY-MHV] Nb happy vertices: " << bestNbHappyVertices << "\n"; // TODO remove
    return solution;
}

void MaximumHappyVertices::GreedyMHV::colourAllVertices(DataStructures::MutableColouring* colouringToColour, DataStructures::ColourType colour) const
{
    for (DataStructures::VertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
    {
        if (!colouring.isColoured(vertex))
        {
            colouringToColour->setColour(vertex, colour);
        }
    }
}
