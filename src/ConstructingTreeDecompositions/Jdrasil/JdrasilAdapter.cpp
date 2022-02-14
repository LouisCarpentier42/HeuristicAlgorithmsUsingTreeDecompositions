//
// Created by louis on 09/09/2021.
//

#include "JdrasilAdapter.h"

void Jdrasil::computeNiceTreeDecomposition(const std::string& graphFile, const std::string& treeFile)
{
    char command[256];
    sprintf(command,
            R"(cd ../../src/ConstructingTreeDecompositions/Jdrasil && java -jar JdrasilAdapter.jar "nice_decomposition" "../../../GraphFiles/%s" "../../../TreeDecompositionFiles/%s")",
            graphFile.c_str(), treeFile.c_str());
    system(command);
}

void Jdrasil::computeVeryNiceTreeDecomposition(const std::string& graphFile, const std::string& treeFile)
{
    char command[256];
    sprintf(command,
            R"(cd ../../src/ConstructingTreeDecompositions/Jdrasil && java -jar JdrasilAdapter.jar "very_nice_decomposition" "../../../GraphFiles/%s" "../../../TreeDecompositionFiles/%s")",
            graphFile.c_str(), treeFile.c_str());
    system(command);
}

void Jdrasil::computeExactTreeDecomposition(const std::string& graphFile)
{
    char command[128];
    sprintf(command,
            R"(cd ../../src/ConstructingTreeDecompositions/Jdrasil && java -jar JdrasilAdapter.jar "exact" "../../../GraphFiles/%s")",
            graphFile.c_str());
    system(command);
}

void Jdrasil::computeHeuristicTreeDecomposition(const std::string& graphFile)
{
    char command[128];
    sprintf(command,
            R"(cd ../../src/ConstructingTreeDecompositions/Jdrasil && java -jar JdrasilAdapter.jar "heuristic" "../../../GraphFiles/%s")",
            graphFile.c_str());
    system(command);
}

void Jdrasil::computeApproximateTreeDecomposition(const std::string& graphFile)
{
    char command[128];
    sprintf(command,
            R"(cd ../../src/ConstructingTreeDecompositions/Jdrasil && java -jar JdrasilAdapter.jar "approximate" "../../../GraphFiles/%s")",
            graphFile.c_str());
    system(command);
}