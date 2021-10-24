//
// Created by louis on 23/10/2021.
//

#include "Graph.h"

#include <algorithm>

DataStructures::Graph::Graph(size_t nbVertices, std::vector<std::vector<vertexType>> adjacencyList) :
    nbVertices{nbVertices}, adjacencyList{std::move(adjacencyList)}
{}

size_t DataStructures::Graph::getNbVertices() const
{
    return nbVertices;
}

bool DataStructures::Graph::areNeighbours(vertexType vertex1, vertexType vertex2) const
{
    return std::find(adjacencyList[vertex1].begin(), adjacencyList[vertex1].end(), vertex2) != adjacencyList[vertex1].end();
}

size_t DataStructures::Graph::getDegree(vertexType vertex) const
{
    return adjacencyList[vertex].size();
}

const std::vector<vertexType>* DataStructures::Graph::getNeighbours(vertexType vertex) const
{
    return &adjacencyList[vertex];
}
