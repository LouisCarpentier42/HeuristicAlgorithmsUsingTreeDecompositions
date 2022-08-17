//
// Created by louis on 14/02/2022.
//
// Copyright (c) KU Leuven 2021-2022
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONSTRUCTOR_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONSTRUCTOR_H

#include "../IO/Reader.h"

#include <string>

namespace ConstructTreeDecompositions
{
    enum class ConstructionAlgorithm
    {
        FlowCutter
    };

    class Constructor
    {
    private:
        const IO::Reader& reader;
        const std::string& flowCutterDir;
        const std::string& jdrasilDir;

    public:
        Constructor(
            const IO::Reader& reader,
            const std::string& flowCutterDir,
            const std::string& jdrasilDir
        );

        std::string construct(ConstructionAlgorithm algorithm, const std::string& graphFile, double time);
        std::string constructNice(ConstructionAlgorithm algorithm, const std::string& graphFile, double time);

    private:
        std::string constructWithFlowCutter(const std::string& graphFile, double time);
    };
}



#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_CONSTRUCTOR_H
