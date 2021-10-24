//
// Created by louis on 23/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H

#include <vector>

namespace DataStructures {

    class Graph
    {
    private:
        const int nbVertices;
        const int nbEdges;
        const std::vector<std::vector<int>> adjacencyList;

    public:
        Graph(int nbVertices, int nbEdges, std::vector<std::vector<int>> adjacencyList);

        bool areNeighbours(int vertex1, int vertex2) const;
        unsigned int getDegree(int vertex) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H
