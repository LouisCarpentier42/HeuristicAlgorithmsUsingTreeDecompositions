//
// Created by louis on 24/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H

#include "../DataStructrures/Graph.h"
#include "../CustomTypes.h"

#include <vector>

class Colouring
{
private:
    const DataStructures::Graph* graph;
    const std::vector<colourType> initialColouring;
    const colourType nbColours;
    std::vector<colourType> colouring;

public:
    Colouring(DataStructures::Graph* graph, std::vector<colourType> initialColouring);

    [[nodiscard]] colourType getColour(vertexType vertex) const;
    void setColour(vertexType vertex, colourType colour);
    [[nodiscard]] bool isPrecoloured(vertexType vertex) const;
    [[nodiscard]] bool isColoured(vertexType vertex) const;

    [[nodiscard]] unsigned int getNbHappyVertices() const;
};

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
