//
// Created by louis on 08/12/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H

namespace ExperimentalAnalysis
{

    struct Experiment
    {
        std::string graphName{};
        size_t nbColours{};
        size_t nbColouringsToKeep{};
        size_t nbRepetitionsPerColouring{};
        size_t nbColouringsPerGraph{};
    };
}


#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_EXPERIMENT_H
