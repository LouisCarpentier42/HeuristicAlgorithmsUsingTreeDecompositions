
#include "ConstructingTreeDecompositions/TreeDecompositionSolverTimer.h"
#include "ConstructingTreeDecompositions/FlowCutter/FlowCutterAdapter.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"

#include "IO/Reader.h"
#include "DataStructures/TreeDecomposition/Bag.h"
#include "DataStructures/Graph/Graph.h"
#include "DataStructures/TreeDecomposition/TreeDecomposition.h"

#include "DataStructures/Colouring/MutableColouring.h"
#include "DataStructures/Colouring/Colouring.h"
#include "Solvers/SolverBase.h"
#include "Solvers/MaximumHappyVertices/ConstructionAlgorithms/GreedyMHV.h"
#include "Solvers/MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h"
#include "Solvers/MaximumHappyVertices/HeuristicTreeDecompositionAlgorithms/HeuristicTreeDecompositionSolver.h"

#include <iostream>
#include <random>


DataStructures::Colouring generatePartialColouring(DataStructures::Graph& graph, int nbColours, double percentColouredVertices)
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

    return DataStructures::Colouring{colourVector};
}

int main()
{
    IO::Reader reader{
        "../GraphFiles/",
        "../TreeDecompositionFiles/"};

    std::string graphName{"he005"};
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
    std::cout << "Treewidth: " << niceTreeDecomposition.getTreeWidth() << "\n";
    std::cout << niceTreeDecomposition;


    auto partialColouring = generatePartialColouring(graph, 5, 0.01);
    std::cout << "Original colouring: " << partialColouring << '\n';
//    auto solver = MaximumHappyVertices::HeuristicTreeDecompositionSolver{graph, partialColouring, niceTreeDecomposition};
    auto greedySolver = MaximumHappyVertices::GreedyMHV{graph, partialColouring};
//    auto growthSolver = MaximumHappyVertices::GrowthMHV{graph, partialColouring};
//    DataStructures::MutableColouring* colouring = solver.solve();
    DataStructures::MutableColouring* colouringGreedy = greedySolver.solve();
//    DataStructures::MutableColouring* colouringGrowth = growthSolver.solve();

//    std::cout << "My colouring:       " << *colouring << '\n';
    std::cout << "Greedy colouring:   " << *colouringGreedy << '\n';
//    std::cout << "Growth colouring:   " << *colouringGrowth << '\n';


    std::cout << "--- TEST --\n";
    std::vector<int> x{1,2,3,4,5};
    std::vector<int> y{1,2,3,4,5};
    std::cout << "x==y " << (x==y) << "\n";
    std::cout << "x==x " << (x==x) << "\n";
    std::cout << "y==y " << (y==y) << "\n";

}
