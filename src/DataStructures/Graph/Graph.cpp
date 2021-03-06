//
// Created by louis on 23/10/2021.
//

#include "Graph.h"

#include <algorithm>

DataStructures::Graph::Graph(std::vector<Vertex> vertices)
    : nbVertices{vertices.size()}, vertices{std::move(vertices)}, nbColours{0}
{
    for (const DataStructures::Vertex& vertex : this->vertices)
    {
        if (nbColours < vertex.colour)
            nbColours = vertex.colour;
    }
}

size_t DataStructures::Graph::getNbColours() const
{
    return nbColours;
}

size_t DataStructures::Graph::getNbVertices() const
{
    return nbVertices;
}

DataStructures::ColourType DataStructures::Graph::getColour(DataStructures::VertexType vertexType) const
{
    return vertices[vertexType].colour;
}

bool DataStructures::Graph::isPrecoloured(DataStructures::VertexType vertexType) const
{
    return vertices[vertexType].isPrecoloured;
}

bool DataStructures::Graph::isColoured(DataStructures::VertexType vertexType) const
{
    return vertices[vertexType].isColoured;
}

size_t DataStructures::Graph::getDegree(DataStructures::VertexType vertexType) const
{
    return vertices[vertexType].degree;
}

const std::vector<DataStructures::VertexType>& DataStructures::Graph::getNeighbours(DataStructures::VertexType vertexType) const
{
    return vertices[vertexType].neighbours;
}

double DataStructures::Graph::getPercentPrecoloured() const
{
    double nbPrecoloured{0.0};
    for (const Vertex& vertex : vertices)
    {
        if (vertex.isPrecoloured)
            nbPrecoloured += 1.0;
    }
    return nbPrecoloured / (double)vertices.size();
}


void DataStructures::Graph::setColour(DataStructures::VertexType vertexType, DataStructures::ColourType colour)
{
    if (!vertices[vertexType].isPrecoloured && colour != 0)
    {
        vertices[vertexType].colour = colour;
        vertices[vertexType].isColoured = true;
    }
}

void DataStructures::Graph::setInitialColour(DataStructures::VertexType vertex, DataStructures::ColourType colour)
{
    vertices[vertex].colour = colour;
    vertices[vertex].isColoured = true;
    vertices[vertex].isPrecoloured = true;
    if (colour > nbColours)
        nbColours = colour;
}

void DataStructures::Graph::removeColours()
{
    for (DataStructures::Vertex& vertex : vertices)
    {
        if (!vertex.isPrecoloured)
        {
            vertex.colour = 0;
            vertex.isColoured = false;
        }
    }
}

void DataStructures::Graph::removeInitialColours()
{
    for (DataStructures::Vertex& vertex : vertices)
    {
        vertex.colour = 0;
        vertex.isColoured = false;
        vertex.isPrecoloured = false;
    }
    nbColours = 0;
}

std::string DataStructures::Graph::getColourString() const
{
    std::string result = "[" + std::to_string(vertices[0].colour);
    for (int i{1}; i < nbVertices; i++)
        result += ", " + std::to_string(vertices[i].colour);
    return result + "]";
}
