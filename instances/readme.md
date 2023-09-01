# Instances

This directory contains all the instances used for experimentation. Details on how the instances were generated is given below. For some of the types multiple zip files are included. This is because the file sizes may not exceed 100MB, and thus the different instances of a certain type must be divided into multiple files. 

The tree decompositions were generated using [FlowCutter](https://github.com/kit-algo/flow-cutter-pace17) [1], which was given at most 2.5 seconds to construct a tree decomposition. This time was even further reduced for smaller graphs after some minor experimentations. All the tree decompositions in this directory are nice tree decompositions. We used [Jdrasil](https://github.com/maxbannach/Jdrasil) [2] to convert the tree decompositions constructed by FlowCutter into nice tree decompositions.

The format of the graphs and tree decompositions is as described by the [PACE 2017 Challenge](https://pacechallenge.org/2017/treewidth/) [3].

## SMAC

The instances used for tuning the algorithm with [SMAC](https://github.com/automl/SMAC3) [4] were generated using the generator of Rhyd Lewis et al. [5], which can be downloaded through the following link: http://www.rhydlewis.eu/resources/happygen.zip.

Several configurations were used for generating instances, with varying number of vertices, number of colours, percentage of initially coloured vertices, and graph density. The instances are separated in directories for each configuration with the name 'LewisGeneratedRandom', followed by the 4 parameters seperated by an underscore in order as stated in the previous sentence. If the graph density is said to be 'default', then it is equal to 5/(n+1), which resulted in the hardest instances according to Lewis et Al., with n the number of vertices. 

The 15 train instances for SMAC were generated with seeds 12345 up to 12359. The test instance had seed 54321.

A more elaborate description of this generator is given below. 

## Erdős–Rényi [6]

The generator of Lewis was also used for generating Erdős–Rényi graphs, since it follows exactly this model as discussed below. The naming of the files is identical to those for SMAC. For these instances, we used the seeds 1 to 5. 

Additionally, we received the Erdős–Rényi graphs from prof. Ghirardi, which he used for the validation of his matheuristic [7]. We gratefully thank prof. Ghirardi for providing us with these instances, and for allowing is to make them publicly available. Due to the size of the tree decomposition for these graphs, we have not added them in this directory.

## Classes

These files contain the instances of specific graph classes. These were obtained from the [House of Graphs](https://hog.grinvin.org/) database [8]. All the small graphs are available on their [graph meta-directory](https://hog.grinvin.org/MetaDirectory.action), except for the small eulerian graphs which are made publicly availble by Brendan McKay on [this webpage](http://users.cecs.anu.edu.au/~bdm/data/graphs.html). The interesting graphs are available in the [database of interesting graphs](https://hog.grinvin.org/StartNewSearch.action) on House of Graphs. We will also mention the download date of these interesting graphs, since researchers can add new interesting graphs to this database. The claw-free graphs, planar graphs and trees were downloaded on the 22th of April. The other graphs - bipartite, cubic, Eulerian and non-Hamiltonian graphs - were downloaded on the 24th of april. 

## Generator of Rhyd Lewis et al. [5]

We will give some details to how exactly the generator of Rhyd Lewis generates instances for the MHV problem. Given a number of vertices n, a graph density p, a number of colours k, and a percentage of initially coloured vertices q. If q*n < k is satisifed, then an illegal configuration is given because there are too few vertices that must be coloured for all k colours, and no instance will be generated. Otherwise, the generator constructs a graph according to the Erdős–Rényi model. For this an initially empty graph with n vertices is constructed. Next, all pairs of vertices are considered, and an edge between a pair is added with probability p. Then the colouring is constructed by randomly ordering the vertices. The first k vertices in this permutation are coloured in colours 1 to k, respectively. The next floor(qn)-k vertices are assigned a random colour. 


# References

[1] Hamann, Michael, and Ben Strasser. "Graph bisection with pareto optimization." Journal of Experimental Algorithmics (JEA) 23 (2018): 1-34.

[2] Bannach, Max, and Sebastian Berndt. "Practical Access to Dynamic Programming on Tree Decompositions, 2018." URL: http://drops. dagstuhl. de/opus/volltexte/2018/9469, doi 10.

[3] Dell, Holger, et al. "The PACE 2017 parameterized algorithms and computational experiments challenge: The second iteration." 12th international symposium on parameterized and exact computation (IPEC 2017). Schloss Dagstuhl-Leibniz-Zentrum fuer Informatik, 2018.

[4] Hutter, Frank, Holger H. Hoos, and Kevin Leyton-Brown. "Sequential model-based optimization for general algorithm configuration." Learning and Intelligent Optimization: 5th International Conference, LION 5, Rome, Italy, January 17-21, 2011. Selected Papers 5. Springer Berlin Heidelberg, 2011.

[5] Lewis, Rhyd, Dhananjay Thiruvady, and Kerri Morgan. "Finding happiness: an analysis of the maximum happy vertices problem." Computers & Operations Research 103 (2019): 265-276.

[6] Erdős, Paul, and Alfréd Rényi. "On the evolution of random graphs." Publ. math. inst. hung. acad. sci 5.1 (1960): 17-60.

[7] Ghirardi, Marco, and Fabio Salassa. "A simple and effective algorithm for the maximum happy vertices problem." Top 30.1 (2022): 181-193.

[8] Coolsaet, Kris, Sven D’hondt, and Jan Goedgebeur. "House of Graphs 2.0: A database of interesting graphs and more." Discrete Applied Mathematics 325 (2023): 97-107.
