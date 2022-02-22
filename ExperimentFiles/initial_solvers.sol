c
c Each line represents a 'command', with the first word the command and the next words the arguments
c
c Lines that start with a 'c' are comments and ignored
c
c The line that starts with 'problem' decides the problem that will be solved
c There must be exactly 1 such line in the file
c Note that no check is performed to see if the solvers are compatible with the problem
c
c Furthermore there must be exactly one line starting with 'nbRepetitions' followed by an integer.
c This number dictates how many times all solvers (baseline and heuristic TD) are executed on each problem instance.
c
c Lines that start with 'baseline' are the baseline solvers used for comparison
c
c Lines starting with heuristicTD represent settings for the heuristic solver using tree decompositions
c The arguments are as follows:
c - The name/identifier for the solver (must be unique)
c - the number of colour functions that should be kept
c - the evaluator to be used (potentially with its parameters)
c - the handler for leaf nodes (potentially with its parameters)
c - the handler for introduce nodes (potentially with its parameters)
c - the handler for forget nodes (potentially with its parameters)
c - the handler for join nodes (potentially with its parameters)
c
problem MaximumHappyVertices
baseline greedyMHV
baseline growthMHV
nbRepetitions 1
heuristicTD basic 8 basicMHVEvaluator passive bestColour bestColour staticOrder(avg,0.01,gdf)
heuristicTD potential 8 potentialHappyMHVEvaluator(6,2,-1) passive bestColour bestColour dynamicOrder(avg,0.01,mostColouredNeighbours)
heuristicTD growth 8 growthMHVEvaluator(6,-1,4,2,2,-1,0) passive bestColour bestColour greedyColourBag(avg,0.01)