c
c Each line represents a 'command', with the first word the command and the next words the arguments
c
c Lines that start with a 'c' are comments and ignored
c
c The line that starts with 'problem' decides the problem that will be solved
c There must be exactly 1 such line in the file
c Note that no check is performed to see if the solvers are compatible with the problem
c
c Lines that start with baseline are the baseline solvers used for comparison
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
nbRepetitions 2
baseline greedyMHV
baseline growthMHV
heuristicTD tdAlgo_min 8 uncolouredMHVEvaluator(6,2,-1,5,1,-1) passive bestColour passive greedyColourBag(min)
heuristicTD tdAlgo_max 8 colouredMHVEvaluator(6,2,-1) passive bestColour passive greedyColourBag(max)
heuristicTD tdAlgo_avg 8 colouredMHVEvaluator(6,2,-1) passive bestColour passive greedyColourBag(avg)
c heuristicTD greedyColourBag2 8 colouredMHVEvaluator(6,2,-1) passive bestColour passive greedyColourBag(min)
c heuristicTD mostCol 8 colouredMHVEvaluator(6,2,-1) passive bestColour passive dynamicOrder(mostColouredNeighbours,avg)
c heuristicTD fewestCol 8 colouredMHVEvaluator(6,2,-1) passive bestColour passive dynamicOrder(DynamicOrderJoinNodeHandler,avg)
c heuristicTD mostHappy 8 colouredMHVEvaluator(6,2,-1) passive bestColour passive dynamicOrder(mostPotentialHappyNeighbours,avg)
c heuristicTD most%Happy 8 colouredMHVEvaluator(6,2,-1) passive bestColour passive dynamicOrder(mostPercentPotentialHappyNeighbours,avg)