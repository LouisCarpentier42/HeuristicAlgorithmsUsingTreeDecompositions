
#include "ConstructingTreeDecompositions/TreeDecompositionSolverTimer.h"
#include "ConstructingTreeDecompositions/FlowCutter/FlowCutterAdapter.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"

#include "IO/Reader.h"
#include "DataStructrures/Bags/Bag.h"
#include "DataStructrures/Graph.h"
#include "DataStructrures/TreeDecomposition.h"

#include "DataStructrures/Colouring.h"
#include "DataStructrures/PartialColouring.h"
#include "MaximumHappyVertices/MaximumHappyVerticesSolver.h"
#include "MaximumHappyVertices/ConstructionAlgorithms/GreedyMHV.h"
#include "MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h"
#include "MaximumHappyVertices/HeuristicTreeDecompositionAlgorithms/HeuristicTreeDecompositionSolver.h"

#include <iostream>

int main()
{
    IO::Reader reader{
        "../GraphFiles/",
        "../TreeDecompositionFiles/"};

    std::string graphName{"ex002"};
    std::string graphFile{graphName + ".gr"};
    std::string treeFile{graphName + ".tw"};
    std::string niceTreeFile{graphName + "_nice.tw"};
    std::string veryNiceTreeFile{graphName + "_very_nice.tw"};

//    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//    timer.executeSolver(graphFile);
//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);

//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeVeryNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);

    DataStructures::Graph graph = reader.readGraph(graphFile);
//    DataStructures::TreeDecomposition treeDecomposition = reader.readTreeDecomposition(niceTreeFile);
//    std::cout << treeDecomposition;
    DataStructures::NiceTreeDecomposition niceTreeDecomposition = reader.readNiceTreeDecomposition(niceTreeFile);
    std::cout << niceTreeDecomposition;


    auto partialColouring = DataStructures::generatePartialColouring(graph, 3, 0.1);
    auto solver = MaximumHappyVertices::HeuristicTreeDecompositionSolver{graph, partialColouring, niceTreeDecomposition};
    auto greedySolver = MaximumHappyVertices::GreedyMHV{graph, partialColouring};
    DataStructures::Colouring* colouring = solver.solve();
    DataStructures::Colouring* colouringGreedy = greedySolver.solve();


    std::cout << "Original colouring: " << partialColouring << '\n';
    std::cout << "My colouring:       " << *colouring << '\n';
    std::cout << "Greedy colouring:   " << *colouringGreedy << '\n';

    return 0;
}
