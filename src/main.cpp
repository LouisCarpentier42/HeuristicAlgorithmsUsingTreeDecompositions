
#include "ExperimentalAnalysis/Experiment.h"
#include "ExperimentalAnalysis/experimentalAnalysis.h"
#include "IO/Reader.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"

#include <set>


int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

//    DataStructures::Vertex vertex{0};
//
//    std::cout << vertex.colour << "\n";
//    vertex.colour = 1;
//    std::cout << vertex.colour << "\n";
//    return 0;


    std::string graphFilesDir = "../GraphFiles/";
    std::string treeDecompositionFilesDir = "../TreeDecompositionFiles/";
    std::string experimentFilesDir = "../ExperimentFiles/";
    IO::Reader reader{
        graphFilesDir,
        treeDecompositionFilesDir,
        experimentFilesDir
    };

//    std::string name{"my_first_graph"};
//    std::string graphFile{name + ".gr"};
//    std::string treeFile{name + ".tw"};
//    std::string niceTreeFile{name + "_nice.tw"};
//    auto td = reader.readTreeDecomposition(treeFile);
//    std::cout << td;
//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//
//    auto ntd = reader.readNiceTreeDecomposition(niceTreeFile);
//    std::cout << ntd;

    std::string solverFile{"initial_solvers.sol"};
    std::string experimentFile{"initial_experiment.exp"};
    ExperimentalAnalysis::Experiment experiment = reader.readExperiment(solverFile, experimentFile);
    ExperimentalAnalysis::executeExperiment(reader, experiment);


//    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//    timer.executeSolver(graphFile);
//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);

//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeVeryNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);
}
