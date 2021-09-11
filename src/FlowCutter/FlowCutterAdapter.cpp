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

#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>


// TODO find a way to decide how many seconds to give to each graph
void FlowCutter::computeHeuristicTreeDecomposition(const std::string& graphFile, int time)
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


// TODO improvements:
//      - Put in class
//      - Choose what the maximum amount of time is that should be run
//      - Choose the multiplier to increase the time
//      - Check if the is big or not (not just if the bag size is equal)
//      - More intelligently choose the initial time? ie start at time=60 for big graphs
//      - Choose which solver you want to use
void FlowCutter::autoTimer(const std::string& graphFile)
{
    int time{1};
    int smallestBagSizeFound{2147483647};

    while (time <= 600) {
        computeHeuristicTreeDecomposition(graphFile, time);

        // TODO let methods return (a pointer to) the name of the output file
        char outFileName[128];
        sprintf(outFileName, "../TreeDecompositionFiles/%s.tw", graphFile.substr(0, graphFile.size()-3).c_str());

        std::ifstream file{outFileName};
        std::string line{'c'};
        while (file && line[0] != 's')
        {
            std::getline(file, line);
            if (line[0] == 's') {

                // Tokenize
                std::vector<std::string> tokens;
                std::istringstream iss(line);
                copy(std::istream_iterator<std::string>(iss),
                     std::istream_iterator<std::string>(),
                     back_inserter(tokens));

                // Convert to int
                int largestBagSize;
                std::stringstream ss;
                ss << tokens[3];
                ss >> largestBagSize;

                // Second check is to verify that the tree decomposition is not just one bag containing all the nodes
                if (largestBagSize >= smallestBagSizeFound && tokens[3] != tokens[4]) {
                    std::cout << "Found a decomposition in time " << time << '\n';
                    return;
                }

                smallestBagSizeFound = largestBagSize;
            }
        }

        std::cout << "Done iteration with time " << time << ", current bag size is " << smallestBagSizeFound << '\n';
        time *= 2;
    }
}
