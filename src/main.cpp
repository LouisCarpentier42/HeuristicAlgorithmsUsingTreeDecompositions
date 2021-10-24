
#include "TreeDecompositionSolverTimer.h"
#include "FlowCutter/FlowCutterAdapter.h"
#include "Jdrasil/JdrasilAdapter.h"


#include "IO/Reader.h"
#include "DataStructrures/Bag.h"
#include "DataStructrures/Graph.h"
#include "DataStructrures/TreeDecomposition.h"
#include "MaximumHappyVertices/Colouring.h"

#include <iostream>

#include <algorithm> // TODO remove

int main()
{
    std::string graphName{"my_first_graph"};
    std::string graphFile{graphName + ".gr"};
    std::string treeFile{graphName + ".tw"};
    std::string niceTreeFile{graphName + "_nice.tw"};
    std::string veryNiceTreeFile{graphName + "_very_nice.tw"};

//    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//    timer.executeSolver(graphFile);

//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 120);

//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);

    IO::Reader reader{"../GraphFiles/", "../TreeDecompositionFiles/"};

    DataStructures::Graph* graph = reader.readGraph(graphFile);
    std::vector<colourType> v{0,1,2,3,4,5};
    Colouring c{graph, v};






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
