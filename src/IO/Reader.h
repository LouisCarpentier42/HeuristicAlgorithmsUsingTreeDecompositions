//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H

#include "../DataStructrures/Bag.h"
#include "../DataStructrures/TreeDecomposition.h"
#include "../DataStructrures/Graph.h"

#include <string>

namespace IO
{
    class Reader
    {
    private:
        const std::string graphFilesDir;
        const std::string treeDecompositionFilesDir;

    public:
        Reader(std::string graphFilesDir, std::string treeDecompositionFilesDir);

        DataStructures::TreeDecomposition* readTreeDecomposition(std::string& filename) const;
        DataStructures::Graph readGraph(std::string& filename) const;

    private:
        static std::vector<std::string> tokenize(std::string& line);
        static int convertToInt(std::string& str);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
