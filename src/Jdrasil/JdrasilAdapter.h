//
// Created by louis on 09/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JDRASILADAPTER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JDRASILADAPTER_H

#include <string>

namespace Jdrasil {

    void computeNiceTreeDecompositions();

    void computeExactTreeDecomposition(std::string& graphFile);
    void computeHeuristicTreeDecomposition(std::string& graphFile);
    void computeApproximateTreeDecomposition(std::string& graphFile);

}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_JDRASILADAPTER_H
