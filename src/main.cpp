
#include "ConstructingTreeDecompositions/TreeDecompositionSolverTimer.h"
#include "ConstructingTreeDecompositions/FlowCutter/FlowCutterAdapter.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"

#include "IO/Reader.h"
#include "DataStructrures/Bag.h"
#include "DataStructrures/Graph.h"
#include "DataStructrures/TreeDecomposition.h"

#include "MaximumHappyVertices/Colouring/Colouring.h"
#include "MaximumHappyVertices/Colouring/PartialColouring.h"
#include "MaximumHappyVertices/MaximumHappyVerticesSolver.h"
#include "MaximumHappyVertices/ConstructionAlgorithms/GreedyMHV.h"
#include "MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h"

#include <iostream>

int main()
{
    IO::Reader reader{
        "../GraphFiles/",
        "../TreeDecompositionFiles/"};

//    std::string graphName{"test_growth_mhv"};
    std::string graphName{"he100"};
    std::string graphFile{graphName + ".gr"};
    std::string treeFile{graphName + ".tw"};
    std::string niceTreeFile{graphName + "_nice.tw"};
    std::string veryNiceTreeFile{graphName + "_very_nice.tw"};

//    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//    timer.executeSolver(graphFile);

//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);
//
//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);
//
//    DataStructures::TreeDecomposition* treeDecomposition = reader.readTreeDecomposition(treeFile);
//    std::cout << *treeDecomposition;
//    std::cout << "----------------------------------\n";
//    DataStructures::TreeDecomposition* niceTreeDecomposition = reader.readTreeDecomposition(niceTreeFile);
//    std::cout << *niceTreeDecomposition;
//    std::cout << "----------------------------------\n";
//    DataStructures::TreeDecomposition* veryNiceTreeDecomposition = reader.readTreeDecomposition(veryNiceTreeFile);
//    std::cout << *veryNiceTreeDecomposition;


    int nbColours{5};
    DataStructures::Graph graph = reader.readGraph(graphFile);
    std::cout << "#vertices: " << graph.getNbVertices() << '\n';

//    std::vector<colourType> colourVector(graph.getNbVertices());
//    colourVector[0] = 1;
//    colourVector[1] = 1;
//    colourVector[2] = 2;
//    colourVector[3] = 3;
//    colourVector[4] = 1;
//    colourVector[5] = 2;
//    colourVector[6] = 3;
//    colourVector[7] = 2;
//    colourVector[8] = 3;
//
//    MaximumHappyVertices::PartialColouring partialColouring{colourVector};
//    auto solver = MaximumHappyVertices::GrowthMHV{graph, partialColouring};
//    MaximumHappyVertices::Colouring* colouring = solver.solve();
//    std::cout << *colouring << '\n';


    for (int i{0}; i < 1; i++) {
        auto partialColouring = MaximumHappyVertices::generatePartialColouring(graph, nbColours, 0.1);
//        std::cout << partialColouring << "\n";
        auto greedySolver = MaximumHappyVertices::GreedyMHV{graph, partialColouring};
        auto growthSolver = MaximumHappyVertices::GrowthMHV{graph, partialColouring};
        MaximumHappyVertices::Colouring* colouringGreedy = greedySolver.solve();
        MaximumHappyVertices::Colouring* colouringGrowth = growthSolver.solve();
//        std::cout << *colouring << '\n';
        std::cout << "-------------------------------------\n";
    }

    return 0;
}
