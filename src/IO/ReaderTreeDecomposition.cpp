//
// Created by louis on 11/11/2021.
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
    std::vector<std::pair<std::shared_ptr<DataStructures::StandardNode>, std::shared_ptr<DataStructures::StandardNode>>> edges(nbBags-1);

    std::getline(file, line);
    tokens = tokenize(line);
    while (file && (line[0] == 'b' || line[0] == 'c'))
    {
        if (tokens[0] != "c") {
            int bagId{convertToInt(tokens[1])};
            size_t bagSize{tokens.size()-2}; // Minus 2 because first token is 'b' and second token is bag id
            std::set<DataStructures::VertexType> vertices{};
            for (int i = 2; i < tokens.size(); i++)
            {
                vertices.insert(convertToInt(tokens[i])-1);
            }
            bags[bagId-1] = std::make_shared<DataStructures::StandardNode>(bagId, bagSize, vertices);
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
    std::vector<std::shared_ptr<DataStructures::StandardNode>> parents(bags.size() + 1, nullptr);
    while (!bagsToProcess.empty()) {
        std::shared_ptr<DataStructures::StandardNode> bagBeingProcessed{bagsToProcess.front()};
        for (std::pair<std::shared_ptr<DataStructures::StandardNode>, std::shared_ptr<DataStructures::StandardNode>> edge : edges) {
            if (bagBeingProcessed == edge.first) {
                if (parents[bagBeingProcessed->getId()] != edge.second) {
                    bagBeingProcessed->addChild(edge.second);
                    bagsToProcess.push(edge.second);
                    parents[edge.second->getId()] = bagBeingProcessed;
                }
            }
            else if (bagBeingProcessed == edge.second) {
                if (parents[bagBeingProcessed->getId()] != edge.first) {
                    bagBeingProcessed->addChild(edge.first);
                    bagsToProcess.push(edge.first);
                    parents[edge.first->getId()] = bagBeingProcessed;
                }
            }
        }
        bagsToProcess.pop();
    }
    return std::make_shared<DataStructures::TreeDecomposition>(largestBagSize-1, root);
}
