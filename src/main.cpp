
#include "FlowCutter/FlowCutterAdapter.h"
#include "TreeDecomposition/Bag.h"
#include "TreeDecomposition/Reader.h"

#include <iostream>


int main()
{
//    FlowCutter::computeTreeDecomposition("my_first_graph.gr", 5);

    std::string fileName{"test.tw"};
    TreeDecomposition::Bag* bag = TreeDecomposition::read(fileName);
    std::cout << *bag << '\n';

    return 0;
}

