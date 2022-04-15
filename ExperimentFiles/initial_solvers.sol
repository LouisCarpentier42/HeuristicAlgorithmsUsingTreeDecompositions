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
problem MaximumHappyVertices
baseline greedyMHV
baseline growthMHV
nbRepetitions 1
c heuristicTD_V2 merge_1 1 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 merge_4 4 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 merge_8 8 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 merge_16 16 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 merge_32 32 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 merge_64 64 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 merge_128 128 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 merge_256 256 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 merge_512 512 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 merge_1024 1024 2 1 0 0 randomRankingOut unitary merge
c heuristicTD_V2 copyBag_1 1 2 1 0 0 randomRankingOut unitary copyBag
c heuristicTD_V2 copyBag_4 4 2 1 0 0 randomRankingOut unitary copyBag
c heuristicTD_V2 copyBag_8 8 2 1 0 0 randomRankingOut unitary copyBag
c heuristicTD_V2 copyBag_16 16 2 1 0 0 randomRankingOut unitary copyBag
c heuristicTD_V2 copyBag_32 32 2 1 0 0 randomRankingOut unitary copyBag
c heuristicTD_V2 copyBag_64 64 2 1 0 0 randomRankingOut unitary copyBag
c heuristicTD_V2 copyBag_128 128 2 1 0 0 randomRankingOut unitary copyBag
heuristicTD_V2 copyBag_256 256 2 1 0 0 randomRankingOut unitary copyBag
c heuristicTD_V2 copyBag_512 512 2 1 0 0 randomRankingOut unitary copyBag
c heuristicTD_V2 copyBag_1024 1024 2 1 0 0 randomRankingOut unitary copyBag