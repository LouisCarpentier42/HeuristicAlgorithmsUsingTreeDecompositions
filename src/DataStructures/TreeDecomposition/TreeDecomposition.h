//
// Created by louis on 10/09/2021.
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
        const T* root;

    public:
        TreeDecompositionTemplate(int treeWidth, T* root) : treeWidth{treeWidth}, root{root} {}
        [[nodiscard]] int getTreeWidth() const { return treeWidth; }
        [[nodiscard]] const T* getRoot() const { return root; }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& out, const TreeDecompositionTemplate<T>& treeDecomposition)
    {
        return out << *treeDecomposition.getRoot();
    }

    using NiceTreeDecomposition = TreeDecompositionTemplate<NiceNode>;
    using TreeDecomposition = TreeDecompositionTemplate<Node>;
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_TREEDECOMPOSITION_H
