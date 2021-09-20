//
// Created by louis on 11/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONSOLVERTIMER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONSOLVERTIMER_H

#include <string>

// TODO improvements
//      - Choose which solver you want to use
//      - Initially multiply time and after some time increment (eg add a minute)?
class TreeDecompositionSolverTimer
{
private:
    const double initialTime;
    const double timeMultiplier;
    const double maxTime;
    const double improvementRatio;

public:
    TreeDecompositionSolverTimer(double initialTime, double timeMultiplier, double maxTime, double improvementRatio);
    void executeSolver(const std::string& graphFile) const;

private:
    bool improvementTooSmall(int currentTreeWidth, int bestTreeWidth) const;
};


#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITIONSOLVERTIMER_H
