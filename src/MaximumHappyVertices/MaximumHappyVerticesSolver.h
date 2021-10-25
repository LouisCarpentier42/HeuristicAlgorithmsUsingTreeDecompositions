//
// Created by louis on 25/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H

#include "Colouring.h"
#include "../DataStructrures/Graph.h"

namespace MaximumHappyVertices
{
    class MaximumHappyVerticesSolver
    {
    protected:
        const DataStructures::Graph* graph;
        const Colouring* colouring;

    public:
        MaximumHappyVerticesSolver(const DataStructures::Graph* graph, const Colouring* colouring);

        virtual Colouring* solve() = 0;
    };

    // TODO find better place for this function
    unsigned int getNbHappyVertices(const DataStructures::Graph* graph, const Colouring* colouring)
    {
        unsigned int nbHappyVertices{0};

        for (vertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
        {
            bool vertexIsHappy{true};
            for (vertexType neighbour : *graph->getNeighbours(vertex))
            {
                // TODO throw error if some vertex is uncoloured
                if (colouring->getColour(neighbour) != colouring->getColour(vertex))
                {
                    vertexIsHappy = false;
                    break;
                }
            }
            if (vertexIsHappy)
            {
                nbHappyVertices++;
            }
        }
        return nbHappyVertices;
    }
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_MAXIMUMHAPPYVERTICESSOLVER_H
