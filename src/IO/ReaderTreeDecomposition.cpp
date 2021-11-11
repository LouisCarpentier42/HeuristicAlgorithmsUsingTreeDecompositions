//
// Created by louis on 11/11/2021.
//

#include "Reader.h"

DataStructures::TreeDecomposition IO::Reader::readTreeDecomposition(std::string& filename) const
{
    std::ifstream file{treeDecompositionFilesDir + filename};
    if (!file)
    {
        throw std::runtime_error("Can't read tree decomposition in '" + filename + "' because the file can't be opened!");
    }

    std::string line{"c"};
    while (file && line[0] != 's')
    {
        std::getline(file, line);
    }

    std::vector<std::string> tokens = tokenize(line);
    int nbBags{convertToInt(tokens[2])};
    int largestBagSize{convertToInt(tokens[3])};
    int nbVertices{convertToInt(tokens[4])};

    std::vector<DataStructures::StandardBag*> bags(nbBags);
    std::vector<std::pair<DataStructures::StandardBag*, DataStructures::StandardBag*>> edges(nbBags-1);

    std::getline(file, line);
    tokens = tokenize(line);
    while (file && (line[0] == 'b' || line[0] == 'c'))
    {
        if (tokens[0] != "c") {
            int bagId{convertToInt(tokens[1])};
            size_t bagSize{tokens.size()-2};
            std::vector<DataStructures::VertexType> vertices(bagSize);
            for (int i = 0; i < vertices.size(); i++)
            {
                vertices[i] = convertToInt(tokens[i+2]);
            }
            bags[bagId-1] = new DataStructures::StandardBag{bagId, bagSize, vertices};
        }
        std::getline(file, line);
        tokens = tokenize(line);
    }

    while (file) {
        if (!(tokens.empty() || tokens[0] == "c")){
            edges.emplace_back(
                    bags[convertToInt(tokens[0])-1],
                    bags[convertToInt(tokens[1])-1]
                    );
        }
        std::getline(file, line);
        tokens = tokenize(line);
    }

    // Use the first empty bag as root and otherwise use the first bag
    DataStructures::StandardBag* root{bags[0]};
    for (DataStructures::StandardBag* bag : bags) {
        if (bag->isEmpty()) {
            root = bag;
            break;
        }
    }

    std::vector<DataStructures::StandardBag*> bagsToProcess{root};
    while (!bagsToProcess.empty()) {
        DataStructures::StandardBag* bagBeingProcessed{bagsToProcess[0]};
        for (std::pair<DataStructures::StandardBag*, DataStructures::StandardBag*> edge : edges) {
            if (bagBeingProcessed == edge.first) {
                if (bagBeingProcessed->getParent() != edge.second) {
                    bagBeingProcessed->addChild(edge.second);
                    bagsToProcess.push_back(edge.second);
                }
            }
            else if (bagBeingProcessed == edge.second) {
                if (bagBeingProcessed->getParent() != edge.first) {
                    bagBeingProcessed->addChild(edge.first);
                    bagsToProcess.push_back(edge.first);
                }
            }
        }
        bagsToProcess.erase(bagsToProcess.begin());
    }
    return DataStructures::TreeDecomposition{largestBagSize-1, root};
}
