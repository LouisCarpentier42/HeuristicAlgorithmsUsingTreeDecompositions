//
// Created by louis on 14/02/2022.
//

#include <sys/stat.h>
#include "Constructor.h"

ConstructTreeDecompositions::Constructor::Constructor(
        const IO::Reader& reader,
        const std::string& flowCutterDir,
        const std::string& jdrasilDir)
    : reader{reader},
      flowCutterDir{flowCutterDir},
      jdrasilDir{jdrasilDir}
{}

std::string ConstructTreeDecompositions::Constructor::construct(ConstructionAlgorithm algorithm, const std::string& graphFile, double time)
{
    switch (algorithm)
    {
        case ConstructionAlgorithm::FlowCutter:
            return constructWithFlowCutter(graphFile, time);
    }
}

std::string ConstructTreeDecompositions::Constructor::constructNice(ConstructionAlgorithm algorithm, const std::string& graphFile, double time)
{
    // Create the tree decomposition
    std::string treeDecompositionFileName = construct(algorithm, graphFile, time);

    // Create the nice tree decomposition
    system((
        "java -jar " + jdrasilDir + "JdrasilAdapter.jar \"nice_decomposition\"" +
        " " + reader.graphFilesDir + graphFile +
        " " + reader.treeDecompositionFilesDir + treeDecompositionFileName + ".tw"
    ).c_str());

    // Remove the tree decomposition
    system((
        "rm " + reader.treeDecompositionFilesDir + treeDecompositionFileName + ".tw"
    ).c_str());

    return treeDecompositionFileName + "_nice.tw";
}

std::string ConstructTreeDecompositions::Constructor::constructWithFlowCutter(const std::string &graphFile, double time)
{
    // Create the resulting directory if needed
    if (graphFile.find('/') != std::string::npos)
    {
        IO::Reader::createDirectory(reader.treeDecompositionFilesDir + graphFile.substr(0, graphFile.find_last_of('/')));
    }

    // Execute flow cutter
    system((
            "timeout " + std::to_string(time) + " " +
            flowCutterDir + "/flow_cutter_pace17 " +
            " < " + reader.graphFilesDir + graphFile +
            " > " + reader.treeDecompositionFilesDir + graphFile.substr(0, graphFile.size()-3) + ".tw"
            ).c_str());

    return graphFile.substr(0, graphFile.size()-3);
}
