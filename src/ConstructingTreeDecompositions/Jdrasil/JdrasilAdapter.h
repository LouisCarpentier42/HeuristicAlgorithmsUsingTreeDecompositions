//
// Created by louis on 09/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JDRASILADAPTER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JDRASILADAPTER_H

#include <string>

namespace Jdrasil {

    void computeNiceTreeDecomposition(const std::string& graphFile, const std::string& treeFile);
    void computeVeryNiceTreeDecomposition(const std::string& graphFile, const std::string& treeFile);

    void computeExactTreeDecomposition(const std::string& graphFile);
    void computeHeuristicTreeDecomposition(const std::string& graphFile);
    void computeApproximateTreeDecomposition(const std::string& graphFile);
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JDRASILADAPTER_H
