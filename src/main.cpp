
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
#include <random>


DataStructures::PartialColouring generatePartialColouring(DataStructures::Graph& graph, int nbColours, double percentColouredVertices)
{ // TODO move somewhere else
    static std::mt19937 rng;
    std::uniform_int_distribution<DataStructures::ColourType> colourDistribution(1, nbColours);

    // Create a random shuffling of the vertices and colour them in this order
    std::vector<DataStructures::VertexType> allVertices(graph.getNbVertices());
    for (DataStructures::VertexType vertex{0}; vertex < graph.getNbVertices(); vertex++)
        allVertices[vertex] = vertex;
    std::shuffle(allVertices.begin(), allVertices.end(), rng);

    // Colour the first nbColours vertices in each colour before randomly colour the remaining vertices
    std::vector<DataStructures::ColourType> colourVector(graph.getNbVertices());
    for (int i{0}; i < nbColours; i++)
        colourVector[allVertices[i]] = i+1;
    for (int i{nbColours}; i < percentColouredVertices * graph.getNbVertices(); i++)
        colourVector[allVertices[i]] = colourDistribution(rng);

    return DataStructures::PartialColouring{colourVector};
}

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


    auto partialColouring = generatePartialColouring(graph, 10, 0.1);
    auto solver = MaximumHappyVertices::HeuristicTreeDecompositionSolver{graph, partialColouring, niceTreeDecomposition};
    auto greedySolver = MaximumHappyVertices::GreedyMHV{graph, partialColouring};
    DataStructures::Colouring* colouring = solver.solve();
    DataStructures::Colouring* colouringGreedy = greedySolver.solve();


    std::cout << "Original colouring: " << partialColouring << '\n';
    std::cout << "My colouring:       " << *colouring << '\n';
    std::cout << "Greedy colouring:   " << *colouringGreedy << '\n';

    return 0;
}
