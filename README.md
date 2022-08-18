# HeuristicAlgorithmsUsingTreeDecompositions

## Abstract 

We propose a new approach for developing heuristic algorithms for graph optimisation problems using the tree decomposition of that graph. Traditionally such algorithms construct an optimal solution of the given problem instance through a dynamic programming approach. We modify this procedure by only storing a limited number of all dynamic programming states, and thus only considering a limited number of partial solutions. By doing so we drop the exactness guarantee of our algorithm in favor of a shorter running time. However if this number is large enough such that all partial solutions are considered, then the heuristic algorithm can still guarantee an exact solution. It offers a trade-off between the solution quality of the algorithm and its running time. 
    
Concretely we develop a heuristic algorithm using tree decompositions for the Maximum Happy Vertices problem. Our algorithm constructs high quality solutions for graphs of small treewidth, and can often even prove optimality of the solution for such instances. This exactness guarantee is not available in other heuristic algorithms. Furthermore our algorithm constructs colourings with more happy vertices than existing heuristics Greedy-MHV and Growth-MHV when at least 40% of the vertices are coloured, at the cost of a larger running time. Our algorithm can also more efficiently construct exact solutions than the exact algorithm for graphs of bounded treewidth, which iterates over all possible partial solutions including those that are invalid. 

## Contributors

Author: Louis Carpenteir

In collaboration with: Jan Goedgebeur and Jorik Jooken

## Data availablity

The instances used for experimentation are available in the [instances](instances/) directory. The results of all experiments are available in the [results](results/) directory. 
