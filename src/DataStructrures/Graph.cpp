//
// Created by louis on 23/10/2021.
//

#include "Graph.h"

#include <algorithm>

DataStructures::Graph::Graph(int nbVertices, int nbEdges, std::vector<std::vector<int>> adjacencyList) :
    nbVertices{nbVertices}, nbEdges{nbEdges}, adjacencyList{std::move(adjacencyList)}
{}

bool DataStructures::Graph::areNeighbours(int vertex1, int vertex2) const
{
    return std::find(adjacencyList[vertex1].begin(), adjacencyList[vertex1].end(), vertex2) != adjacencyList[vertex1].end();
}

unsigned int DataStructures::Graph::getDegree(int vertex) const
{
    return adjacencyList[vertex].size();
}