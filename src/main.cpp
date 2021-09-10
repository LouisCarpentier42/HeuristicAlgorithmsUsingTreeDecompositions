
#include "FlowCutter/FlowCutterAdapter.h"
#include "Jdrasil/JdrasilAdapter.h"


#include "DataStructrures//Bag.h"
#include "DataStructrures/Reader.h"
#include "DataStructrures/TreeDecomposition.h"

#include <iostream>

int main()
{
    std::string graphName{"ex001"};
    std::string graphFile{graphName + ".gr"};
    std::string treeFile{graphName + ".tw"};

    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);

    DataStructures::Reader reader{"../GraphFiles/", "../TreeDecompositionFiles/"};
    DataStructures::TreeDecomposition* treeDecomposition = reader.readTreeDecomposition(treeFile);
    std::cout << *treeDecomposition << '\n';

    return 0;
}
