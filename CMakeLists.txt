cmake_minimum_required(VERSION 3.10)
project(HeuristicAlgorithmsUsingTreeDecompositions)

set(CMAKE_CXX_STANDARD 17)

add_executable(HeuristicAlgorithmsUsingTreeDecompositions src/main.cpp src/FlowCutter/FlowCutterAdapter.cpp src/FlowCutter/FlowCutterAdapter.h src/DataStructrures/Bag.cpp src/DataStructrures/Bag.h src/IO/Reader.cpp src/IO/Reader.h src/Jdrasil/JdrasilAdapter.cpp src/Jdrasil/JdrasilAdapter.h src/DataStructrures/TreeDecomposition.cpp src/DataStructrures/TreeDecomposition.h src/TreeDecompositionSolverTimer.cpp src/TreeDecompositionSolverTimer.h src/DataStructrures/Graph.cpp src/DataStructrures/Graph.h src/MaximumHappyVertices/Colouring.cpp src/MaximumHappyVertices/Colouring.h src/CustomTypes.h)
