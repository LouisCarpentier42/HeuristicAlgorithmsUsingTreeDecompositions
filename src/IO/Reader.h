//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H

#include "../DataStructures/TreeDecomposition/Bag.h"
#include "../DataStructures/TreeDecomposition/NiceBag.h"
#include "../DataStructures/TreeDecomposition/LeafBag.h"
#include "../DataStructures/TreeDecomposition/JoinBag.h"
#include "../DataStructures/TreeDecomposition/IntroduceVertexBag.h"
#include "../DataStructures/TreeDecomposition/ForgetVertexBag.h"
#include "../DataStructures/TreeDecomposition/StandardBag.h"
#include "../DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "../DataStructures/Graph/Graph.h"

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
