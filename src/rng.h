//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_RNG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_RNG_H

#include <random>

class RNG
{
public:
    inline static std::mt19937 rng{std::random_device{}()};
    static void setRNG(unsigned int seed = std::random_device{}()) { rng = std::mt19937{seed}; }
};

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_RNG_H
