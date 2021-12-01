
#include "IO/Reader.h"

#include "ConstructingTreeDecompositions/TreeDecompositionSolverTimer.h"
#include "ConstructingTreeDecompositions/FlowCutter/FlowCutterAdapter.h"
#include "ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h"


#include "DataStructures/TreeDecomposition/Bag.h"
#include "DataStructures/TreeDecomposition/TreeDecomposition.h"
#include "DataStructures/Graph/Graph.h"
#include "DataStructures/Colouring/AdvancedMHVEvaluator.h"
#include "DataStructures/Colouring/MutableColouring.h"
#include "DataStructures/Colouring/Colouring.h"


#include "Solvers/SolverBase.h"
#include "Solvers/MaximumHappyVertices/ConstructionAlgorithms/GreedyMHV.h"
#include "Solvers/MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h"
#include "Solvers/HeuristicTreeDecompositionSolver/HeuristicTreeDecompositionSolver.h"
#include "Solvers/HeuristicTreeDecompositionSolver/LeafBagHandler/ConcreteLeafBagHandlers.h"
#include "Solvers/HeuristicTreeDecompositionSolver/IntroduceVertexBagHandler/ConcreteIntroduceVertexBagHandlers.h"
#include "Solvers/HeuristicTreeDecompositionSolver/ForgetVertexBagHandler/ConcreteForgetVertexBagHandlers.h"
#include "Solvers/HeuristicTreeDecompositionSolver/JoinBagHandler/ConcreteJoinBagHandlers.h"


#include <iostream>
#include <random>
#include <map>
#include <chrono>


DataStructures::Colouring generatePartialColouring(DataStructures::Graph& graph, int nbColours, double percentColouredVertices)
{ // TODO move somewhere else
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<DataStructures::ColourType> colourDistribution(1, nbColours);

    // Create a random shuffling of the vertices and colour them in this order
    std::vector<DataStructures::VertexType> allVertices(graph.getNbVertices());
    std::iota(allVertices.begin(), allVertices.end(), 0);
    std::shuffle(allVertices.begin(), allVertices.end(), rng);

    // Colour the first nbColours vertices in each colour before randomly colour the remaining vertices
    std::vector<DataStructures::ColourType> colourVector(graph.getNbVertices());
    for (int i{0}; i < nbColours; i++)
        colourVector[allVertices[i]] = i+1;
    for (int i{nbColours}; i < percentColouredVertices * graph.getNbVertices(); i++)
        colourVector[allVertices[i]] = colourDistribution(rng);

    return DataStructures::Colouring{colourVector};
}

int main(int argc, char** argv)
{
    std::string graphName;
    std::string graphFilesDir;
    std::string TreeDecompositionFilesDir;
    if (argc > 1)
    {
        graphName = argv[1];
        graphFilesDir = "../../GraphFiles/";
        TreeDecompositionFilesDir = "../../TreeDecompositionFiles/";
    }
    else
    {
        graphName = "ex001";
        graphFilesDir = "../GraphFiles/";
        TreeDecompositionFilesDir = "../TreeDecompositionFiles/";
    }

    int nbColours;
    if (argc > 2)
    {
        std::stringstream ss;
        ss << argv[2];
        ss >> nbColours;
    }
    else
    {
        nbColours = 3;
    }

    size_t nbSolutionsToKeep{16};

    std::string graphFile{graphName + ".gr"};
    std::string treeFile{graphName + ".tw"};
    std::string niceTreeFile{graphName + "_nice.tw"};
    std::string veryNiceTreeFile{graphName + "_very_nice.tw"};
    IO::Reader reader{graphFilesDir, TreeDecompositionFilesDir};

//    TreeDecompositionSolverTimer timer{1.0, 4.0, 10000.0, 0.20};
//    timer.executeSolver(graphFile);
//    FlowCutter::computeHeuristicTreeDecomposition(graphFile, 2);

//    Jdrasil::computeNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeVeryNiceTreeDecomposition(graphFile, treeFile);
//    Jdrasil::computeApproximateTreeDecomposition(graphFile);
//    Jdrasil::computeExactTreeDecomposition(graphFile);
//    Jdrasil::computeHeuristicTreeDecomposition(graphFile);

    DataStructures::Graph graph = reader.readGraph(graphFile);
    DataStructures::TreeDecomposition treeDecomposition = reader.readTreeDecomposition(treeFile);
    std::cout << treeDecomposition;
    DataStructures::NiceTreeDecomposition niceTreeDecomposition = reader.readNiceTreeDecomposition(niceTreeFile);
    std::cout << niceTreeDecomposition;

    std::cout << "Treewidth:   " << niceTreeDecomposition.getTreeWidth() << "\n";
    std::cout << "Nb vertices: " << graph.getNbVertices() << "\n";

    DataStructures::Colouring colouring = generatePartialColouring(graph, nbColours, 0.01);
    std::cout << "Original colouring: " << colouring << "\n\n";

    std::map<std::string, Solvers::SolverBase*> solvers{};
    solvers["greedy_mhv"] = new MaximumHappyVertices::GreedyMHV{&graph, &colouring};
    solvers["growth_mhv"] = new MaximumHappyVertices::GrowthMHV{&graph, &colouring};

    DataStructures::AdvancedMHVEvaluator evaluator{&graph, 6, 2, -1};
//    solvers["my_basic_solver"] = new Solvers::HeuristicTreeDecompositionSolver{
//            &graph, &colouring, &evaluator, nbSolutionsToKeep, &niceTreeDecomposition,
//            new Solvers::BasicLeafBagHandlers{},
//            new Solvers::ColourAllIntroduceVertexBagHandler{},
//            new Solvers::BasicForgetVertexBagHandler{},
//            new Solvers::StaticOrderJoinBagHandler{&graph}
//    };
//    solvers["my_basic_solver_gdf"] = new Solvers::HeuristicTreeDecompositionSolver{
//            &graph, &colouring, &evaluator, nbSolutionsToKeep, &niceTreeDecomposition,
//            new Solvers::BasicLeafBagHandlers{},
//            new Solvers::ColourAllIntroduceVertexBagHandler{},
//            new Solvers::BasicForgetVertexBagHandler{},
//            new Solvers::StaticOrderJoinBagHandler{&graph, Solvers::BasicJoinBagHandler::Order::greatestDegreeFirst}
//    };
//    solvers["my_basic_solver_sdf"] = new Solvers::HeuristicTreeDecompositionSolver{
//            &graph, &colouring, &evaluator, nbSolutionsToKeep, &niceTreeDecomposition,
//            new Solvers::BasicLeafBagHandlers{},
//            new Solvers::ColourAllIntroduceVertexBagHandler{},
//            new Solvers::BasicForgetVertexBagHandler{},
//            new Solvers::StaticOrderJoinBagHandler{&graph, Solvers::BasicJoinBagHandler::Order::smallestDegreeFirst}
//    };
//    solvers["my_basic_solver_random"] = new Solvers::HeuristicTreeDecompositionSolver{
//            &graph, &colouring, &evaluator, nbSolutionsToKeep, &niceTreeDecomposition,
//            new Solvers::BasicLeafBagHandlers{},
//            new Solvers::ColourAllIntroduceVertexBagHandler{},
//            new Solvers::BasicForgetVertexBagHandler{},
//            new Solvers::StaticOrderJoinBagHandler{&graph, Solvers::BasicJoinBagHandler::Order::random}
//    };
//    solvers["my_solver_dynamic_order"] = new Solvers::HeuristicTreeDecompositionSolver{
//            &graph, &colouring, &evaluator, nbSolutionsToKeep, &niceTreeDecomposition,
//            new Solvers::BasicLeafBagHandlers{},
//            new Solvers::ColourAllIntroduceVertexBagHandler{},
//            new Solvers::BasicForgetVertexBagHandler{},
//            new Solvers::DynamicOrderJoinBagHandler{}
//    };
    solvers["my_solver_best_colour_introduce"] = new Solvers::HeuristicTreeDecompositionSolver{
            &graph, &colouring, &evaluator, nbSolutionsToKeep, &niceTreeDecomposition,
            new Solvers::BasicLeafBagHandlers{},
            new Solvers::BestColourIntroduceVertexBagHandler{},
            new Solvers::BasicForgetVertexBagHandler{},
            new Solvers::DynamicOrderJoinBagHandler{}
    };

    DataStructures::BasicMHVEvaluator mhvEvaluator{&graph};
    for (auto const& [name, solver] : solvers)
    {
        std::cout << ">>> " << name << " <<<\n";

        auto start = std::chrono::high_resolution_clock::now();
        auto* solution = solver->solve();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "Evaluation: " << mhvEvaluator.evaluate(solution) << "\n";
        std::cout << "Colouring:  " << *solution << "\n";
        std::cout << "Time (µs):  " << duration.count() << "\n\n";
    }
}
