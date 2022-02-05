//
// Created by louis on 04/02/2022.
//

#include "HappyVerticesTableEntry.h"

DataStructures::HappyVerticesTableEntry::HappyVerticesTableEntry(
        int evaluation,
        DataStructures::TableEntry::ColourAssignments &importantColourAssignments,
        DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments& happyVerticesAssignment)
    : TableEntry{evaluation, importantColourAssignments}, happyVertices{happyVerticesAssignment}
{ }

DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments DataStructures::HappyVerticesTableEntry::getHappyVertices()
{
    return happyVertices;
}

DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments::HappyVerticesAssignments(const DataStructures::Graph* graph)
    : vertexIsHappy(graph->getNbVertices(), false) {}

void DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments::makeHappy(DataStructures::VertexType vertex)
{
    vertexIsHappy[vertex] = true;
}

void DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments::makeUnhappy(DataStructures::VertexType vertex)
{
    vertexIsHappy[vertex] = false;
}

bool DataStructures::HappyVerticesTableEntry::HappyVerticesAssignments::isHappy(DataStructures::VertexType vertex)
{
    return vertexIsHappy[vertex];
}



