//
// Created by louis on 23/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H

#include "../CustomTypes.h"

#include <vector>

namespace DataStructures {

    class Graph
    {
    private:
        const size_t nbVertices;
        const std::vector<std::vector<vertexType>> adjacencyList;

    public:
        Graph(size_t nbVertices, std::vector<std::vector<vertexType>> adjacencyList);

        [[nodiscard]] size_t getNbVertices() const;
        [[nodiscard]] bool areNeighbours(vertexType vertex1, vertexType vertex2) const;
        [[nodiscard]] size_t getDegree(vertexType vertex) const;
        [[nodiscard]] const std::vector<vertexType>* getNeighbours(vertexType vertex) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H
