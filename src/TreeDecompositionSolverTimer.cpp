//
// Created by louis on 11/09/2021.
//

#include "TreeDecompositionSolverTimer.h"
#include "FlowCutter/FlowCutterAdapter.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <fstream>


TreeDecompositionSolverTimer::TreeDecompositionSolverTimer
    (double initialTime, double timeMultiplier, double maxTime, double improvementRatio)
        : initialTime{initialTime}, timeMultiplier{timeMultiplier}, maxTime{maxTime}, improvementRatio{improvementRatio}
{}

void TreeDecompositionSolverTimer::executeSolver(const std::string& graphFile) const
{
    double time{initialTime};
    int bestTreeWidth{2147483647};

    while (time <= maxTime) {
        FlowCutter::computeHeuristicTreeDecomposition(graphFile, static_cast<int>(time));

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
                int currentTreeWidth;
                std::stringstream ss;
                ss << tokens[3];
                ss >> currentTreeWidth;
                currentTreeWidth -= 1;

                // Second check is to verify that the tree decomposition is not just one bag containing all the nodes
                if (improvementTooSmall(currentTreeWidth, bestTreeWidth) && tokens[3] != tokens[4]) {
                    std::cout << "Found a decomposition a tree decomposition of with " << currentTreeWidth << '\n';
                    return;
                }
                bestTreeWidth = currentTreeWidth;
            }
        }

        std::cout << "Done iteration with time " << time << ", tree width is " << bestTreeWidth << '\n';
        time *= timeMultiplier;
    }
}


bool TreeDecompositionSolverTimer::improvementTooSmall(int currentTreeWidth, int bestTreeWidth) const
{
    return currentTreeWidth >= (1 - improvementRatio)*bestTreeWidth;
}
