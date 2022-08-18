//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
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
        const std::string graphFilesDir;
        const std::string g6GraphFilesDir;
        const std::string treeDecompositionFilesDir;
        const std::string experimentFilesDir;
        const std::string resultFilesDir;

    public:
        Reader(
            std::string graphFilesDir,
            std::string g6GraphFilesDir,
            std::string treeDecompositionFilesDir,
            std::string experimentFilesDir,
            std::string resultFilesDir
        );

        void readG6File(const std::string& filename) const;
        [[nodiscard]] std::shared_ptr<DataStructures::Graph> readGraph(const std::string& filename) const;
        [[nodiscard]] std::shared_ptr<DataStructures::TreeDecomposition> readTreeDecomposition(const std::string& filename) const;
        [[nodiscard]] std::shared_ptr<DataStructures::NiceTreeDecomposition> readNiceTreeDecomposition(const std::string& filename) const;
        [[nodiscard]] std::shared_ptr<ExperimentalAnalysis::Experiment> readExperiment(const std::string& solversFilename, const std::string& experimentsFilename) const;

        [[nodiscard]] static std::shared_ptr<DataStructures::Evaluator> readEvaluator(const std::string& str);
        [[nodiscard]] static std::shared_ptr<DataStructures::Evaluator> readEvaluator(int argc, char** argv);
        [[nodiscard]] static std::shared_ptr<Solvers::LeafNodeHandler> readLeafNodeHandler(const std::string& str);
        [[nodiscard]] static std::shared_ptr<Solvers::LeafNodeHandler> readLeafNodeHandler(int argc, char** argv);
        [[nodiscard]] static std::shared_ptr<Solvers::IntroduceNodeHandler> readIntroduceNodeHandler(const std::string& str);
        [[nodiscard]] static std::shared_ptr<Solvers::IntroduceNodeHandler> readIntroduceNodeHandler(int argc, char** argv);
        [[nodiscard]] static std::shared_ptr<Solvers::ForgetNodeHandler> readForgetNodeHandler(const std::string& str);
        [[nodiscard]] static std::shared_ptr<Solvers::ForgetNodeHandler> readForgetNodeHandler(int argc, char** argv);
        [[nodiscard]] static std::shared_ptr<Solvers::JoinNodeHandler> readJoinNodeHandler(const std::string& str);
        [[nodiscard]] static std::shared_ptr<Solvers::JoinNodeHandler> readJoinNodeHandler(int argc, char** argv);
        [[nodiscard]] static std::shared_ptr<const Solvers::EvaluationMerger> getEvaluationMerger(const std::string& str);
        [[nodiscard]] static std::string colourGraph(const std::string& str, std::shared_ptr<DataStructures::Graph>& graph);
        [[nodiscard]] static std::string colourGraph(int argc, char** argv, std::shared_ptr<DataStructures::Graph>& graph);

        static std::string getParameter(int argc, char** argv, const std::string& paramName, bool isObligatedParam);
        static std::vector<std::string> tokenize(const std::string& line);
        static int convertToInt(const std::string& str);
        static std::vector<std::string> splitParameters(const std::string& str);
        static void createDirectory(const std::string& dir);
        static bool pathExists(const std::string& path);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONREADER_H
