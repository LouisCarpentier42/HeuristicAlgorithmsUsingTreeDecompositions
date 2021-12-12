//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H

#include "../DataStructures/TreeDecomposition/Node.h"
#include "../DataStructures/TreeDecomposition/NiceNode.h"
#include "../DataStructures/TreeDecomposition/LeafNode.h"
#include "../DataStructures/TreeDecomposition/JoinNode.h"
#include "../DataStructures/TreeDecomposition/IntroduceNode.h"
#include "../DataStructures/TreeDecomposition/ForgetNode.h"
#include "../DataStructures/TreeDecomposition/StandardNode.h"
#include "../DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "../DataStructures/Graph/Graph.h"
#include "../ExperimentalAnalysis/Experiment.h"

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
        const std::string experimentFilesDir;

    public:
        Reader(
            std::string graphFilesDir,
            std::string treeDecompositionFilesDir,
            std::string experimentFilesDir
        );

        [[nodiscard]] DataStructures::Graph* readGraph(const std::string& filename) const;
        [[nodiscard]] DataStructures::TreeDecomposition readTreeDecomposition(const std::string& filename) const;
        [[nodiscard]] DataStructures::NiceTreeDecomposition readNiceTreeDecomposition(const std::string& filename) const;
        [[nodiscard]] ExperimentalAnalysis::Experiment readExperiment(const std::string& solversFilename, const std::string& experimentsFilename) const;

        static std::vector<std::string> tokenize(std::string& line);
        static int convertToInt(std::string& str);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
