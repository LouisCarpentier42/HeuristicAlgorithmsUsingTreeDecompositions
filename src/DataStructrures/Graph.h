//
// Created by louis on 23/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H

#include <vector>

namespace DataStructures {

    using VertexType = unsigned int;

    class Graph
    {
    private:
        const size_t nbVertices;
        const std::vector<std::vector<DataStructures::VertexType>> adjacencyList;

    public:
        Graph(size_t nbVertices, std::vector<std::vector<VertexType>> adjacencyList);

        [[nodiscard]] size_t getNbVertices() const;
        [[nodiscard]] bool areNeighbours(DataStructures::VertexType vertex1, DataStructures::VertexType vertex2) const;
        [[nodiscard]] size_t getDegree(DataStructures::VertexType vertex) const;
        [[nodiscard]] const std::vector<DataStructures::VertexType>* getNeighbours(DataStructures::VertexType vertex) const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H
