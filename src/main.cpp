
#include "FlowCutter/FlowCutterAdapter.h"
#include "Jdrasil/JdrasilAdapter.h"
#include "TreeDecomposition/Bag.h"
#include "TreeDecomposition/Reader.h"

#include <iostream>

int main()
{
    std::string graphFile{"my_first_graph.gr"};
    Jdrasil::computeExactTreeDecomposition(graphFile);
    Jdrasil::computeHeuristicTreeDecomposition(graphFile);
    Jdrasil::computeApproximateTreeDecomposition(graphFile);

    Jdrasil::computeNiceTreeDecompositions();

//    std::string graphFile{"my_first_graph.gr"};
//    FlowCutter::computeTreeDecomposition(graphFile, 2); // TODO miss rename naar computeHeuristicTreeDecomposition (voor consistentie)

//    std::string fileName{"my_first_graph.tw"};
//    TreeDecomposition::Bag* bag = TreeDecomposition::read(fileName);
//    std::cout << *bag << '\n';

    return 0;
}
