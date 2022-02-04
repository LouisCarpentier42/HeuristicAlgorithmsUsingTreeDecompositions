//
// Created by louis on 04/02/2022.
//

#include "HappyVerticesTableEntry.h"

DataStructures::HappyVerticesTableEntry::HappyVerticesTableEntry(
        int evaluation,
        DataStructures::TableEntry::ColourAssignments &importantColourAssignments,
        DataStructures::HappyVerticesTableEntry::HappyVerticesAssignment& happyVerticesAssignment)
    : TableEntry{evaluation, importantColourAssignments}, happyVertices{happyVerticesAssignment}
{ }

DataStructures::HappyVerticesTableEntry::HappyVerticesAssignment DataStructures::HappyVerticesTableEntry::getHappyVertices()
{
    return happyVertices;
}


DataStructures::HappyVerticesTableEntry::HappyVerticesAssignment::HappyVerticesAssignment(const DataStructures::Graph* graph)
    : vertexIsHappy(graph->getNbVertices(), false) {}

void DataStructures::HappyVerticesTableEntry::HappyVerticesAssignment::makeHappy(DataStructures::VertexType vertex)
{
    vertexIsHappy[vertex] = true;
}

void DataStructures::HappyVerticesTableEntry::HappyVerticesAssignment::makeUnhappy(DataStructures::VertexType vertex)
{
    vertexIsHappy[vertex] = false;
}

bool DataStructures::HappyVerticesTableEntry::HappyVerticesAssignment::isHappy(DataStructures::VertexType vertex)
{
    return vertexIsHappy[vertex];
}



