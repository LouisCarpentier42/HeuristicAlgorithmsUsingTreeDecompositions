
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
#include "Solvers/HeuristicTreeDecompositionSolver/HeuristicTreeDecompositionSolver.h"
#include "DataStructures/Colouring/AdvancedMHVEvaluator.h"

#include <iostream>
#include <random>


DataStructures::Colouring generatePartialColouring(DataStructures::Graph& graph, int nbColours, double percentColouredVertices)
{ // TODO move somewhere else
    static std::mt19937 rng{std::random_device{}()};
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

    std::string graphName{"ex100"};
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

    std::cout << "Treewidth:   " << niceTreeDecomposition.getTreeWidth() << "\n";
    std::cout << "Nb vertices: " << graph.getNbVertices() << "\n";

//    DataStructures::Colouring colouring{std::vector<DataStructures::ColourType>{0,0,0,2,0,0,0,0,0,3,1,0,0}};
    DataStructures::Colouring colouring = generatePartialColouring(graph, 3, 0.01);
    std::cout << "Original colouring: " << colouring << '\n';

    DataStructures::AdvancedMHVEvaluator evaluator{&graph, 6, 2, -1};
//    DataStructures::BasicMHVEvaluator evaluator{&graph};
    auto solver = Solvers::HeuristicTreeDecompositionSolver{&graph, &colouring, &evaluator, 16, &niceTreeDecomposition};
    DataStructures::MutableColouring* colouringMyAlgorithm = solver.solve();
    std::cout << "My colouring:       " << *colouringMyAlgorithm << '\n';

    auto greedySolver = MaximumHappyVertices::GreedyMHV{&graph, &colouring};
    DataStructures::MutableColouring* colouringGreedy = greedySolver.solve();
    std::cout << "Greedy colouring:   " << *colouringGreedy << '\n';

    auto growthSolver = MaximumHappyVertices::GrowthMHV{&graph, &colouring};
    DataStructures::MutableColouring* colouringGrowth = growthSolver.solve();
    std::cout << "Growth colouring:   " << *colouringGrowth << '\n';
}
