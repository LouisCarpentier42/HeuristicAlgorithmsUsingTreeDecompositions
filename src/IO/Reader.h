//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H

#include "../DataStructrures/Bags/Bag.h"
#include "../DataStructrures/Bags/NiceBag.h"
#include "../DataStructrures/Bags/LeafBag.h"
#include "../DataStructrures/Bags/JoinBag.h"
#include "../DataStructrures/Bags/IntroduceVertexBag.h"
#include "../DataStructrures/Bags/ForgetVertexBag.h"
#include "../DataStructrures/Bags/StandardBag.h"

#include "../DataStructrures/TreeDecomposition.h"
#include "../DataStructrures/Graph.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

namespace IO
{
    class Reader
    {
    private:
        const std::string graphFilesDir;
        const std::string treeDecompositionFilesDir;

    public:
        Reader(std::string graphFilesDir, std::string treeDecompositionFilesDir);

        DataStructures::Graph readGraph(std::string& filename) const;
        DataStructures::TreeDecomposition readTreeDecomposition(std::string& filename) const;
        DataStructures::NiceTreeDecomposition readNiceTreeDecomposition(std::string& filename) const;

    private:
        static std::vector<std::string> tokenize(std::string& line);
        static int convertToInt(std::string& str);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
