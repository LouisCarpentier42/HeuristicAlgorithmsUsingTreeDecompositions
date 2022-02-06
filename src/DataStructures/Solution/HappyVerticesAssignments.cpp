//
// Created by louis on 06/02/2022.
//

#include "HappyVerticesAssignments.h"

DataStructures::HappyVerticesAssignments::HappyVerticesAssignments(const DataStructures::Graph* graph)
    : vertexIsHappy(graph->getNbVertices(), false)
{}

void DataStructures::HappyVerticesAssignments::makeHappy(DataStructures::VertexType vertex)
{
    vertexIsHappy[vertex] = true;
}

void DataStructures::HappyVerticesAssignments::makeUnhappy(DataStructures::VertexType vertex)
{
    vertexIsHappy[vertex] = false;
}

bool DataStructures::HappyVerticesAssignments::isHappy(DataStructures::VertexType vertex)
{
    return vertexIsHappy[vertex];
}

bool DataStructures::operator==(const DataStructures::HappyVerticesAssignments& h1, const DataStructures::HappyVerticesAssignments& h2)
{
    return h1.vertexIsHappy == h2.vertexIsHappy;
}

bool DataStructures::operator<(const DataStructures::HappyVerticesAssignments& h1, const DataStructures::HappyVerticesAssignments& h2)
{
    return h1.vertexIsHappy < h2.vertexIsHappy;
}
