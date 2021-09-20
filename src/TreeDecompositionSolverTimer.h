//
// Created by louis on 11/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERTIMER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERTIMER_H

#include <string>

// TODO improvements
//      - Choose which solver you want to use
//      - Initially multiply time and after some time increment (eg add a minute)?
class SolverTimer
{
private:
    const double initialTime;
    const double timeMultiplier;
    const double maxTime;

    const double improvementRatio;

public:
    SolverTimer(double initialTime, double timeMultiplier, double maxTime, double improvementRatio);

    void executeSolver(std::string& graphFile);
};


#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_SOLVERTIMER_H
