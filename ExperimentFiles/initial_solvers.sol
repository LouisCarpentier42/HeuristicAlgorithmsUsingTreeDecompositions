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
baseline greedyMHV
baseline growthMHV
heuristicTD basicEvaluator 8 basicMHVEvaluator passive bestColour passive staticOrder(gdf)
c heuristicTD colouredEvaluator 8 colouredMHVEvaluator(6,2,-1) passive bestColour passive staticOrder(gdf)
c heuristicTD basicEvaluator_greedyJoin 8 basicMHVEvaluator passive bestColour passive greedyColourBag
c heuristicTD dynamicOrder 8 basicMHVEvaluator passive bestColour passive dynamicOrder
c heuristicTD colouredEvaluator_greedyJoin 8 colouredMHVEvaluator(6,2,-1) passive bestColour passive greedyColourBag
c heuristicTD uncolouredEvaluator 8 uncolouredMHVEvaluator(6,5,2,2,-1,-1) passive bestColour passive staticOrder(gdf)