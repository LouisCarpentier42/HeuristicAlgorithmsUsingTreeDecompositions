
#include "ExperimentalAnalysis/Experiment.h"
#include "ExperimentalAnalysis/experimentalAnalysis.h"
#include "IO/Reader.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"
#include "DataStructures/Evaluator/PotentialHappyUncolouredMHVEvaluator.h"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    std::string graphFilesDir = "../GraphFiles/";
    std::string treeDecompositionFilesDir = "../TreeDecompositionFiles/";
    std::string experimentFilesDir = "../ExperimentFiles/";
    IO::Reader reader{
        graphFilesDir,
        treeDecompositionFilesDir,
        experimentFilesDir
    };

    std::string solverFile{"initial_solvers.sol"};
    std::string experimentFile{"initial_experiment.exp"};
    ExperimentalAnalysis::Experiment experiment = reader.readExperiment(solverFile, experimentFile);
    ExperimentalAnalysis::executeExperiment(reader, experiment);

//    std::string name{"he005"};
//    std::string graphFile{name + ".gr"};
//    std::string treeFile{name + ".tw"};
//    std::string niceTreeFile{name + "_nice.tw"};
//
//    auto* g = reader.readGraph(graphFile);
//    auto c = std::vector<DataStructures::ColourType>{0, 0, 0, 0, 2, 0, 3, 0, 0, 0, 1, 0, 0};
//    g->setInitialColours(c);
////    DataStructures::BasicMHVEvaluator evaluator = DataStructures::Potenti{};
//    DataStructures::PotentialHappyUncolouredMHVEvaluator evaluator{6,5,2, 1, -1, -1};
//
//    DataStructures::TableEntry::ColourAssignments assignments{g};
//    assignments.assignColour(4, 2);
//    assignments.assignColour(6, 3);
//    assignments.assignColour(10, 1);
//    std::cout << assignments << "\n";
//    int evaluation{evaluator.evaluate({4, 6, 10}, assignments, g, 0)};
//
//    std::cout << "--- 2 -> 1\n";
//    assignments.assignColour(2, 1);
//    evaluation = evaluator.evaluate({2}, assignments, g, evaluation);
//    std::cout << evaluation << "\n";
//
//    std::cout << "--- 7 -> 1\n";
//    assignments.assignColour(7, 1);
//    evaluation = evaluator.evaluate({7}, assignments, g, evaluation);
//    std::cout << evaluation << "\n";
//
//    std::cout << "--- 11 -> 1\n";
//    assignments.assignColour(11, 1);
//    evaluation = evaluator.evaluate({11}, assignments, g, evaluation);
//    std::cout << evaluation << "\n";
//
//    std::cout << "--- 0 -> 1\n";
//    assignments.assignColour(0, 1);
//    evaluation = evaluator.evaluate({0}, assignments, g, evaluation);
//    std::cout << evaluation << "\n";
//
//    std::cout << "--- 3 -> 1\n";
//    assignments.assignColour(3, 1);
//    evaluation = evaluator.evaluate({3}, assignments, g, evaluation);
//    std::cout << evaluation << "\n";
//
//    std::cout << "--- 8 -> 1\n";
//    assignments.assignColour(8, 1);
//    evaluation = evaluator.evaluate({8}, assignments, g, evaluation);
//    std::cout << evaluation << "\n";

//    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//    timer.executeSolver(graphFile);
//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);

//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeVeryNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);

}
