//
// Created by louis on 10/09/2021.
//

#include "TreeDecomposition.h"

namespace DataStructures
{
    TreeDecomposition::TreeDecomposition(int treeWidth, Bag* root, std::vector<Bag *> bags)
        : treeWidth{treeWidth}, root{root}, bags{std::move(bags)}
    {}

    std::ostream& operator<<(std::ostream& out, const TreeDecomposition& treeDecomposition)
    {
        return out << *treeDecomposition.root;
    }
}