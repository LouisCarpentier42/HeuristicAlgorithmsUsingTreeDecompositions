//
// Created by louis on 09/09/2021.
//

#include "JdrasilAdapter.h"

void Jdrasil::computeNiceTreeDecompositions()
{
    system(R"(cd ../src/Jdrasil && java -jar JdrasilAdapter.jar "nice_decomposition" "../../GraphFiles/" "../../TreeDecompositionFiles")");
}

void Jdrasil::computeExactTreeDecomposition(std::string& fileName)
{
    system(R"(cd ../src/Jdrasil && java -jar JdrasilAdapter.jar "exact")");
}

void Jdrasil::computeHeuristicTreeDecomposition(std::string &graphFile)
{
    system(R"(cd ../src/Jdrasil && java -jar JdrasilAdapter.jar "heuristic")");
}

void Jdrasil::computeApproximateTreeDecomposition(std::string &graphFile)
{
    system(R"(cd ../src/Jdrasil && java -jar JdrasilAdapter.jar "approximate")");
}