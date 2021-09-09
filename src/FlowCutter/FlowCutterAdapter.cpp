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


// TODO find a way to decide how many seconds to give to each graph
void FlowCutter::computeTreeDecomposition(std::string& graphFile, int time)
{
    // Initialize the command to run
    char command[128];
    sprintf(command,
            "cd ../src/FlowCutter/flow-cutter-pace17 && timeout %ds ./flow_cutter_pace17 < ../../../GraphFiles/%s",
            time, graphFile.c_str());

    // Create an output file with the same name
    char outFileName[128];
    sprintf(outFileName, "../TreeDecompositionFiles/%s.tw", graphFile.substr(0, graphFile.size()-3).c_str());
    std::ofstream outFile{outFileName};
    if (!outFile) {
        throw std::runtime_error("Output file couldn't be created!");
    }

    std::array<char, 128> buffer{};
    std::unique_ptr<FILE, decltype(&pclose) > pipe(popen(command, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        outFile << buffer.data();
    }
}