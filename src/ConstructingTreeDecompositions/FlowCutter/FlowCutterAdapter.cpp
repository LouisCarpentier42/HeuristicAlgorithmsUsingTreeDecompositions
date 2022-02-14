//
// Created by louis on 02/09/2021.
//

#include "FlowCutterAdapter.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


static const std::string TREE_DECOMPOSITION_DIR = "../../TreeDecompositionFiles/";

void FlowCutter::computeHeuristicTreeDecomposition(const std::string& graphFile, int time)
{
    // Initialize the command to run
    char command[256];
    sprintf(command,
            "cd ../../src/ConstructingTreeDecompositions/FlowCutter/flow-cutter-pace17 && timeout %ds ./flow_cutter_pace17 < ../../../../GraphFiles/%s",
            time, graphFile.c_str());

    std::string treeFileDir = TREE_DECOMPOSITION_DIR;
    std::string graphFormatted = graphFile;
    if (graphFile.find('/') != std::string::npos)
    {
        treeFileDir += graphFile.substr(0, graphFile.find_last_of('/'));
        graphFormatted = graphFile.substr(graphFile.find_last_of('/')+1);
        char mkDirCommand[256];
        sprintf(mkDirCommand, R"(mkdir %s)",treeFileDir.c_str());
        system(mkDirCommand);
    }

    // Create an output file with the same name
    char outFileName[256];
    sprintf(outFileName, "%s/%s.tw", treeFileDir.c_str(), graphFormatted.substr(0, graphFormatted.size()-3).c_str());
    std::ofstream outFile{outFileName};
    if (!outFile) {
        throw std::runtime_error("Output file couldn't be created: " + std::string{outFileName});
    }

    std::array<char, 256> buffer{};
    std::unique_ptr<FILE, decltype(&pclose) > pipe(popen(command, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        outFile << buffer.data();
    }
}
