
#include "FlowCutter/FlowCutterAdapter.h"
#include "TreeDecomposition/Bag.h"
#include "TreeDecomposition/Reader.h"

#include <iostream>

int main()
{
    std::string graphFile{"my_first_graph.gr"};
    FlowCutter::computeTreeDecomposition(graphFile, 2);

    std::string fileName{"my_first_graph.tw"};
    TreeDecomposition::Bag* bag = TreeDecomposition::read(fileName);
    std::cout << *bag << '\n';

    return 0;
}
