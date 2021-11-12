//
// Created by louis on 11/11/2021.
//

#include "Reader.h"

#include <queue>

DataStructures::TreeDecomposition IO::Reader::readTreeDecomposition(std::string& filename) const
{
    std::ifstream file{treeDecompositionFilesDir + filename};
    if (!file)
    {
        throw std::runtime_error("Can't read tree decomposition in '" + filename + "' because the file can't be opened!");
    }

    int rootId{-1};

    std::string line{"c"};
    while (file && line[0] != 's')
    {
        std::getline(file, line);
        std::vector<std::string> tokens = tokenize(line);
        if (rootId == -1 && tokens[0] == "c" && tokens[1] == "ROOT_NICE_TREE")
        {
            rootId = convertToInt(tokens[2]);
        }
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
        else if (rootId == -1 && tokens[1] == "ROOT_NICE_TREE") // From previous if we know (tokens[0] == "c")
        {
            rootId = convertToInt(tokens[2]);
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
        else if (rootId == -1 && tokens[0] == "c" && tokens[1] == "ROOT_NICE_TREE")
        {
            rootId = convertToInt(tokens[2]);
        }

        std::getline(file, line);
        tokens = tokenize(line);
    }

    DataStructures::StandardBag* root{nullptr};
    if (rootId != -1)
    {
        for (DataStructures::StandardBag* bag : bags)
        {
            if (bag->getId() == rootId)
            {
                root = bag;
                break;
            }
        }
    }
    if (root == nullptr) // If the no root id was found or no bag with the found root id was exists
    {
         // Use the first empty bag as root and otherwise use the first bag
        root = bags[0];
        for (DataStructures::StandardBag* bag : bags) {
            if (bag->isEmpty()) {
                root = bag;
                break;
            }
        }
    }

    std::queue<DataStructures::StandardBag*> bagsToProcess{};
    bagsToProcess.push(root);
    while (!bagsToProcess.empty()) {
        DataStructures::StandardBag* bagBeingProcessed{bagsToProcess.front()};
        for (std::pair<DataStructures::StandardBag*, DataStructures::StandardBag*> edge : edges) {
            if (bagBeingProcessed == edge.first) {
                if (bagBeingProcessed->getParent() != edge.second) {
                    bagBeingProcessed->addChild(edge.second);
                    bagsToProcess.push(edge.second);
                }
            }
            else if (bagBeingProcessed == edge.second) {
                if (bagBeingProcessed->getParent() != edge.first) {
                    bagBeingProcessed->addChild(edge.first);
                    bagsToProcess.push(edge.first);
                }
            }
        }
        bagsToProcess.pop();
    }
    return DataStructures::TreeDecomposition{largestBagSize-1, root};
}
