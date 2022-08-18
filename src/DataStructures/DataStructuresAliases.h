//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DATASTRUCTURESALIASES_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DATASTRUCTURESALIASES_H

#include <vector>

namespace DataStructures
{
    using VertexType = unsigned int;
    using ColourType = unsigned int;

    struct Vertex {
        VertexType id;
        ColourType colour{0};
        bool isPrecoloured{false};
        bool isColoured{false};
        size_t degree{0};
        std::vector<VertexType> neighbours{};

        explicit Vertex(VertexType id) : id{id} {}
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_DATASTRUCTURESALIASES_H
