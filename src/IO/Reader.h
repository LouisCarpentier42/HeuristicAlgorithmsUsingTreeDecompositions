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
    public:
        const std::string& graphFilesDir;
        const std::string& g6GraphFilesDir;
        const std::string& treeDecompositionFilesDir;
        const std::string& experimentFilesDir;
        const std::string& resultFilesDir;

    public:
        Reader(
            const std::string& graphFilesDir,
            const std::string& g6GraphFilesDir,
            const std::string& treeDecompositionFilesDir,
            const std::string& experimentFilesDir,
            const std::string& resultFilesDir
        );

        void readG6File(const std::string& filename) const;
        [[nodiscard]] DataStructures::Graph* readGraph(const std::string& filename) const;
        [[nodiscard]] DataStructures::TreeDecomposition readTreeDecomposition(const std::string& filename) const;
        [[nodiscard]] DataStructures::NiceTreeDecomposition readNiceTreeDecomposition(const std::string& filename) const;
        [[nodiscard]] ExperimentalAnalysis::Experiment readExperiment(const std::string& solversFilename, const std::string& experimentsFilename) const;

        [[nodiscard]] static const DataStructures::Evaluator* readEvaluator(const std::string& str);
        [[nodiscard]] static const DataStructures::Evaluator* readEvaluator(int argc, char** argv);
        [[nodiscard]] static Solvers::LeafNodeHandler* readLeafNodeHandler(const std::string& str);
        [[nodiscard]] static Solvers::LeafNodeHandler* readLeafNodeHandler(int argc, char** argv);
        [[nodiscard]] static Solvers::IntroduceNodeHandler* readIntroduceNodeHandler(const std::string& str);
        [[nodiscard]] static Solvers::IntroduceNodeHandler* readIntroduceNodeHandler(int argc, char** argv);
        [[nodiscard]] static Solvers::ForgetNodeHandler* readForgetNodeHandler(const std::string& str);
        [[nodiscard]] static Solvers::ForgetNodeHandler* readForgetNodeHandler(int argc, char** argv);
        [[nodiscard]] static Solvers::JoinNodeHandler* readJoinNodeHandler(const std::string& str);
        [[nodiscard]] static Solvers::JoinNodeHandler* readJoinNodeHandler(int argc, char** argv);
        [[nodiscard]] static Solvers::EvaluationMerger* getEvaluationMerger(const std::string& str);
        [[nodiscard]] static std::map<std::string, std::vector<DataStructures::ColourType>> readColouringVector(const std::string& str, const DataStructures::Graph* graph);
        [[nodiscard]] static std::vector<DataStructures::ColourType> readColouringVector(int argc, char** argv, const DataStructures::Graph* graph);

        static std::string getParameter(int argc, char** argv, const std::string& paramName, bool isObligatedParam);
        static std::vector<std::string> tokenize(const std::string& line);
        static int convertToInt(const std::string& str);
        static std::vector<std::string> splitParameters(const std::string& str);
        static void createDirectory(const std::string& dir);
        static bool pathExists(const std::string& path);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
