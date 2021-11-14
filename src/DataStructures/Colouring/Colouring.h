//
// Created by louis on 24/10/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H

#include "../DataStructuresAliases.h"
#include "../Graph/Graph.h"

#include <iostream>
#include <vector>

namespace DataStructures
{
    class Colouring
    {
    protected:
        std::vector<DataStructures::ColourType> colouring;
        const size_t nbColours;

    public:
        explicit Colouring(std::vector<DataStructures::ColourType> colouring);

    protected:
        explicit Colouring(const DataStructures::Colouring* colouring);

    public:
        [[nodiscard]] size_t getNbVertices() const;
        [[nodiscard]] size_t getNbColours() const;
        [[nodiscard]] bool isColoured(DataStructures::VertexType vertex) const;
        [[nodiscard]] DataStructures::ColourType getColour(DataStructures::VertexType vertex) const;

        bool operator==(const DataStructures::Colouring& other) const;
    };

    std::ostream& operator<<(std::ostream& out, const Colouring& colouring);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_COLOURING_H
