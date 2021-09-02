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


void FlowCutter::computeTreeDecomposition(const char* graphFile, int time) {

    char command[128];
    sprintf(command,
            "cd ../src/FlowCutter/flow-cutter-pace17 && timeout %ds ./flow_cutter_pace17 < ../../GraphFiles/%s.gr",
            time, graphFile);

    char outFileName[128];
    sprintf(outFileName, "../src/TreeDecompositionFiles/%s.tw", graphFile);
    std::ofstream outFile{outFileName};
    if (!outFile) {
        throw std::runtime_error("Output file couldn't be created!");
    }

    std::array<char, 128> buffer{};
    std::unique_ptr<FILE, decltype(&pclose) > pipe(popen(reinterpret_cast<const char *>(command), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        outFile << buffer.data();
    }
}