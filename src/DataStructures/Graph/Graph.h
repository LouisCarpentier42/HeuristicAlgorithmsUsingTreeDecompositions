//
// Created by louis on 23/10/2021.
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

        void setColour(VertexType vertexType, ColourType colour);
        void setInitialColours(std::vector<DataStructures::ColourType>& colours);
        void setInitialColour(DataStructures::VertexType vertex, DataStructures::ColourType colour);
        void removeColours();
        void removeInitialColours();

        [[nodiscard]] std::string getColourString() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_GRAPH_H
