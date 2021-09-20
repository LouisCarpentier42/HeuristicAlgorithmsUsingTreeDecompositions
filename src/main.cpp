
#include "TreeDecompositionSolverTimer.h"
#include "FlowCutter/FlowCutterAdapter.h"
#include "Jdrasil/JdrasilAdapter.h"

#include "DataStructrures//Bag.h"
#include "DataStructrures/Reader.h"
#include "DataStructrures/TreeDecomposition.h"

#include <iostream>

int main()
{
    std::string graphName{"he200"};
    std::string graphFile{graphName + ".gr"};
    std::string treeFile{graphName + ".tw"};
    std::string niceTreeFile{graphName + "_nice.tw"};
    std::string veryNiceTreeFile{graphName + "_very_nice.tw"};

    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
    timer.executeSolver(graphFile);

//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 120);

//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);

    DataStructures::Reader reader{"../GraphFiles/", "../TreeDecompositionFiles/"};

//    DataStructures::TreeDecomposition* treeDecomposition = reader.readTreeDecomposition(treeFile);
//    std::cout << *treeDecomposition;
//    std::cout << "----------------------------------\n";
//    DataStructures::TreeDecomposition* niceTreeDecomposition = reader.readTreeDecomposition(niceTreeFile);
//    std::cout << *niceTreeDecomposition;
//    std::cout << "----------------------------------\n";
//    DataStructures::TreeDecomposition* veryNiceTreeDecomposition = reader.readTreeDecomposition(veryNiceTreeFile);
//    std::cout << *veryNiceTreeDecomposition;

    return 0;
}
