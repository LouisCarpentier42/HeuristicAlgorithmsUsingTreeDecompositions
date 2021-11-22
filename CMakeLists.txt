cmake_minimum_required(VERSION 3.10)
project(HeuristicAlgorithmsUsingTreeDecompositions)

set(CMAKE_CXX_STANDARD 17)

add_executable(HeuristicAlgorithmsUsingTreeDecompositions
        src/main.cpp src/ConstructingTreeDecompositions/FlowCutter/FlowCutterAdapter.cpp
        src/ConstructingTreeDecompositions/FlowCutter/FlowCutterAdapter.h
        src/DataStructures/TreeDecomposition/Bag.cpp
        src/DataStructures/TreeDecomposition/Bag.h
        src/IO/Reader.cpp
        src/IO/Reader.h
        src/ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.cpp
        src/ConstructingTreeDecompositions/Jdrasil/JdrasilAdapter.h
        src/DataStructures/TreeDecomposition/TreeDecomposition.h
        src/ConstructingTreeDecompositions/TreeDecompositionSolverTimer.cpp
        src/ConstructingTreeDecompositions/TreeDecompositionSolverTimer.h
        src/DataStructures/Graph/Graph.cpp
        src/DataStructures/Graph/Graph.h
        src/DataStructures/Colouring/Colouring.cpp
        src/DataStructures/Colouring/Colouring.h
        src/Solvers/SolverBase.h
        src/Solvers/MaximumHappyVertices/ConstructionAlgorithms/GreedyMHV.cpp
        src/Solvers/MaximumHappyVertices/ConstructionAlgorithms/GreedyMHV.h
        src/DataStructures/Colouring/MutableColouring.cpp
        src/DataStructures/Colouring/MutableColouring.h
        src/Solvers/MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.cpp
        src/Solvers/MaximumHappyVertices/ConstructionAlgorithms/GrowthMHV.h
        src/Solvers/HeuristicTreeDecompositionSolver/HeuristicTreeDecompositionSolver.cpp
        src/Solvers/HeuristicTreeDecompositionSolver/HeuristicTreeDecompositionSolver.h
        src/DataStructures/TreeDecomposition/NiceBag.cpp
        src/DataStructures/TreeDecomposition/NiceBag.h
        src/DataStructures/TreeDecomposition/StandardBag.cpp
        src/DataStructures/TreeDecomposition/StandardBag.h
        src/DataStructures/TreeDecomposition/IntroduceVertexBag.cpp
        src/DataStructures/TreeDecomposition/IntroduceVertexBag.h
        src/DataStructures/TreeDecomposition/ForgetVertexBag.cpp
        src/DataStructures/TreeDecomposition/ForgetVertexBag.h
        src/DataStructures/TreeDecomposition/IntroduceForgetVertexBagBase.cpp
        src/DataStructures/TreeDecomposition/IntroduceForgetVertexBagBase.h
        src/DataStructures/TreeDecomposition/JoinBag.cpp
        src/DataStructures/TreeDecomposition/JoinBag.h
        src/DataStructures/TreeDecomposition/LeafBag.cpp
        src/DataStructures/TreeDecomposition/LeafBag.h
        src/IO/ReaderGraph.cpp
        src/IO/ReaderTreeDecomposition.cpp
        src/IO/ReaderNiceTreeDecomposition.cpp
        src/DataStructures/DataStructuresAliases.h
        src/DataStructures/Colouring/ColouringQueue.cpp
        src/DataStructures/Colouring/ColouringQueue.h
        src/DataStructures/Colouring/ColouringEvaluator.cpp
        src/DataStructures/Colouring/ColouringEvaluator.h
        src/DataStructures/Colouring/BasicMHVEvaluator.cpp
        src/DataStructures/Colouring/BasicMHVEvaluator.h
        src/Solvers/MaximumHappyVertices/MaximumHappyVerticesSolver.cpp
        src/Solvers/MaximumHappyVertices/MaximumHappyVerticesSolver.h
        src/DataStructures/Colouring/AdvancedMHVEvaluator.cpp
        src/DataStructures/Colouring/AdvancedMHVEvaluator.h
        src/Solvers/HeuristicTreeDecompositionSolver/ForgetVertexBagHandler/BasicForgetVertexBagHandler.cpp
        src/Solvers/HeuristicTreeDecompositionSolver/ForgetVertexBagHandler/ConcreteForgetVertexBagHandlers.h
        src/Solvers/HeuristicTreeDecompositionSolver/LeafBagHandler/BasicLeafBagHandler.cpp
        src/Solvers/HeuristicTreeDecompositionSolver/LeafBagHandler/ConcreteLeafBagHandlers.h
        src/Solvers/HeuristicTreeDecompositionSolver/JoinBagHandler/BasicJoinBagHandler.cpp
        src/Solvers/HeuristicTreeDecompositionSolver/JoinBagHandler/ConcreteJoinBagHandlers.h
        src/Solvers/HeuristicTreeDecompositionSolver/IntroduceVertexBagHandler/BasicIntroduceVertexBagHandler.cpp
        src/Solvers/HeuristicTreeDecompositionSolver/IntroduceVertexBagHandler/ConcreteIntroduceVertexBagHandlers.h
        src/Solvers/HeuristicTreeDecompositionSolver/JoinBagHandler/BasicJoinBagHandler.cpp src/Solvers/HeuristicTreeDecompositionSolver/JoinBagHandler/DynamicOrderJoinBagHandler.cpp)
