//
// Copyright (c) KU Leuven 2021-2022
//
// Author: Louis Carpentier
// In collaboration with: Jan Goedgebeur and Jorik Jooken
//

#include "Reader.h"

#include <queue>

std::shared_ptr<DataStructures::TreeDecomposition> IO::Reader::readTreeDecomposition(const std::string& filename) const
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

    std::vector<std::shared_ptr<DataStructures::StandardNode>> bags(nbBags);
    std::getline(file, line);
    tokens = tokenize(line);
    while (file && (line[0] == 'b' || line[0] == 'c'))
    {
        if (tokens[0] != "c") {
            int bagId{convertToInt(tokens[1])};
            size_t bagSize{tokens.size()-2}; // Minus 2 because first token is 'b' and second token is bag id
            DataStructures::BagContent content{};
            for (int i = 2; i < tokens.size(); i++)
            {
                content.insert(convertToInt(tokens[i]) - 1);
            }
            bags[bagId-1] = std::make_shared<DataStructures::StandardNode>(bagId, bagSize, content);
        }
        std::getline(file, line);
        tokens = tokenize(line);
    }

    std::vector<std::set<int>> edges(nbBags);
    while (file) {
        if (!(tokens.empty() || tokens[0] == "c")){
            int id1 = convertToInt(tokens[0])-1;
            int id2 = convertToInt(tokens[1])-1;

            edges[id1].insert(id2);
            edges[id2].insert(id1);
        }
        std::getline(file, line);
        tokens = tokenize(line);
    }

    std::shared_ptr<DataStructures::StandardNode> root;
    if (rootId != -1)
    {
        for (std::shared_ptr<DataStructures::StandardNode>& bag : bags)
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
        for (std::shared_ptr<DataStructures::StandardNode>& bag : bags) {
            if (bag->isEmpty()) {
                root = bag;
                break;
            }
        }
    }

    std::queue<std::shared_ptr<DataStructures::StandardNode>> bagsToProcess{};
    bagsToProcess.push(root);
//    std::vector<std::shared_ptr<DataStructures::StandardNode>> parents(bags.size() + 1, nullptr);
    while (!bagsToProcess.empty()) {
        std::shared_ptr<DataStructures::StandardNode> bagBeingProcessed{bagsToProcess.front()};
        int bagBeingProcessedId{bagBeingProcessed->getId() - 1};
        for (int otherBagId : edges[bagBeingProcessedId])
        {
            bagBeingProcessed->addChild(bags[otherBagId]);
            bagsToProcess.push(bags[otherBagId]);
            edges[otherBagId].erase(bagBeingProcessedId);
        }
        edges[bagBeingProcessedId].clear();
        bagsToProcess.pop();
    }
    return std::make_shared<DataStructures::TreeDecomposition>(largestBagSize-1, root);
}
