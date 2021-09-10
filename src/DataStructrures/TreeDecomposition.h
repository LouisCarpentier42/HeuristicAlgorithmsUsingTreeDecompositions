//
// Created by louis on 10/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITION_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITION_H

#include "Bag.h"

#include <utility>
#include <vector>
#include <iostream>

namespace DataStructures
{
    class TreeDecomposition
    {
    private:
        int treeWidth;
        Bag* root;
        std::vector<Bag*> bags; // TODO is this needed?

    public:
        TreeDecomposition(int treeWidth, Bag* root, std::vector<Bag*> bags);

        friend std::ostream& operator<<(std::ostream& out, const TreeDecomposition& treeDecomposition);
    };


}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITION_H
