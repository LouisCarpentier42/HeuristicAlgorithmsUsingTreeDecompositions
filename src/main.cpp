
#include "FlowCutter/FlowCutterAdapter.h"
#include "Jdrasil/JdrasilAdapter.h"

#include "DataStructrures//Bag.h"
#include "DataStructrures/Reader.h"
#include "DataStructrures/TreeDecomposition.h"

#include <iostream>

int main()
{
    std::string graphName{"my_first_graph"};
    std::string graphFile{graphName + ".gr"};
    std::string treeFile{graphName + ".tw"};
    std::string niceTreeFile{graphName + "_nice.tw"};
    std::string veryNiceTreeFile{graphName + "_very_nice.tw"};

    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);

    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);

    DataStructures::Reader reader{"../GraphFiles/", "../TreeDecompositionFiles/"};

    DataStructures::TreeDecomposition* treeDecomposition = reader.readTreeDecomposition(treeFile);
    std::cout << *treeDecomposition;
    std::cout << "----------------------------------\n";
    DataStructures::TreeDecomposition* niceTreeDecomposition = reader.readTreeDecomposition(niceTreeFile);
    std::cout << *niceTreeDecomposition;
    std::cout << "----------------------------------\n";
    DataStructures::TreeDecomposition* veryNiceTreeDecomposition = reader.readTreeDecomposition(veryNiceTreeFile);
    std::cout << *veryNiceTreeDecomposition;

    return 0;
}
