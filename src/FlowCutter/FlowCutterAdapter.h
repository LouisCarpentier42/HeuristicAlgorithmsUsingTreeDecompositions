//
// Created by louis on 02/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_FLOWCUTTERADAPTER_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_FLOWCUTTERADAPTER_H

namespace FlowCutter {

    /// Computes the tree decomposition of a graph making use of flow-cutter.
    /// (https://github.com/kit-algo/flow-cutter-pace17)
    ///
    /// \param graphFile
    ///        The file containing the graph. The file must be formatted such as
    ///        described in the PACE 2017 challenge description (for the format
    ///        see https://pacechallenge.org/2017/treewidth/ appendix A). The file
    ///        must be located in src/GraphFiles/ and have a '.gr' extension, but
    ///        the extension should not be provided to this method.
    /// \param time
    ///        The amount of seconds that the flow-cut algorithm has in order to
    ///        compute a tree decomposition.
    void computeTreeDecomposition(const char* graphFile, int time);

}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_FLOWCUTTERADAPTER_H
