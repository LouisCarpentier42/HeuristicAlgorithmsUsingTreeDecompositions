cmake_minimum_required(VERSION 3.10)
project(HeuristicAlgorithmsUsingTreeDecompositions)

set(CMAKE_CXX_STANDARD 17)

add_executable(HeuristicAlgorithmsUsingTreeDecompositions src/main.cpp src/FlowCutter/FlowCutterAdapter.cpp src/FlowCutter/FlowCutterAdapter.h src/TreeDecomposition/Bag.cpp src/TreeDecomposition/Bag.h src/TreeDecomposition/Reader.cpp src/TreeDecomposition/Reader.h src/Jdrasil/JdrasilAdapter.cpp src/Jdrasil/JdrasilAdapter.h)
