//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITION_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITION_H

#include "Node.h"
#include "NiceNode.h"

#include <utility>
#include <vector>
#include <iostream>

namespace DataStructures
{
    template <typename T>
    class TreeDecompositionTemplate
    {
    private:
        const int treeWidth;
        std::shared_ptr<T> root;

    public:
        TreeDecompositionTemplate(int treeWidth, std::shared_ptr<T> root) : treeWidth{treeWidth}, root{root} {}
        [[nodiscard]] int getTreeWidth() const { return treeWidth; }
        [[nodiscard]] std::shared_ptr<T> getRoot() { return root; }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& out, TreeDecompositionTemplate<T>& treeDecomposition)
    {
        return out << *treeDecomposition.getRoot();
    }

    using NiceTreeDecomposition = TreeDecompositionTemplate<NiceNode>;
    using TreeDecomposition = TreeDecompositionTemplate<Node>;
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITION_H
