//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H

#include "Bag.h"
#include "TreeDecomposition.h"

#include <string>

namespace DataStructures
{
    class Reader
    {
    private:
        const std::string graphFilesDir;
        const std::string treeDecompositionFilesDir;

    public:
        Reader(std::string graphFilesDir, std::string treeDecompositionFilesDir);

        TreeDecomposition* readTreeDecomposition(std::string& fileName) const;

    private:
        static std::vector<std::string> tokenize(std::string& line);
        static int convertToInt(std::string& str);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
