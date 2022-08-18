//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H

#include "../DataStructuresAliases.h"

#include <vector>
#include <string>

namespace DataStructures
{
    class Graph
    {
    private:
        size_t nbColours{0};
        const size_t nbVertices;
        std::vector<Vertex> vertices;

    public:
        explicit Graph(std::vector<Vertex> vertices);

        [[nodiscard]] size_t getNbColours() const;
        [[nodiscard]] size_t getNbVertices() const;
        [[nodiscard]] ColourType getColour(VertexType vertexType) const;
        [[nodiscard]] bool isPrecoloured(VertexType vertexType) const;
        [[nodiscard]] bool isColoured(VertexType vertexType) const;
        [[nodiscard]] size_t getDegree(VertexType vertexType) const;
        [[nodiscard]] const std::vector<VertexType>& getNeighbours(VertexType vertexType) const;
        [[nodiscard]] double getPercentPrecoloured() const; 

        void setColour(VertexType vertexType, ColourType colour);
        void setInitialColour(DataStructures::VertexType vertex, DataStructures::ColourType colour);
        void removeColours();
        void removeInitialColours();

        [[nodiscard]] std::string getColourString() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H
