//
// Created by louis on 03/09/2021.
//
#include "Reader.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>


namespace IO
{
    Reader::Reader(std::string graphFilesDir, std::string treeDecompositionFilesDir)
        : graphFilesDir{std::move(graphFilesDir)}, treeDecompositionFilesDir{std::move(treeDecompositionFilesDir)}
    {}

    DataStructures::TreeDecomposition* Reader::readTreeDecomposition(std::string& filename) const
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

        std::vector<DataStructures::Bag*> bags(nbBags);
        std::vector<std::pair<DataStructures::Bag*, DataStructures::Bag*>> edges(nbBags-1);

        std::getline(file, line);
        tokens = tokenize(line);
        while (file && (line[0] == 'b' || line[0] == 'c'))
        {
            if (tokens[0] != "c") {
                int bagId{convertToInt(tokens[1])};
                size_t bagSize{tokens.size()-2};
                std::vector<int> vertices(bagSize);
                for (int i = 0; i < vertices.size(); i++)
                {
                    vertices[i] = convertToInt(tokens[i+2]);
                }
                bags[bagId-1] = new DataStructures::Bag{bagId, bagSize, vertices};
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
        DataStructures::Bag* root{bags[0]};
        for (DataStructures::Bag* bag : bags) {
            if (bag->isEmpty()) {
                root = bag;
                break;
            }
        }

        std::vector<DataStructures::Bag*> bagsToProcess{root};
        while (!bagsToProcess.empty()) {
            DataStructures::Bag* bagBeingProcessed{bagsToProcess[0]};
            for (std::pair<DataStructures::Bag*, DataStructures::Bag*> edge : edges) {
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

        return new DataStructures::TreeDecomposition{largestBagSize-1, root, bags};
    }

    DataStructures::Graph Reader::readGraph(std::string &filename) const
    {
        std::ifstream file{graphFilesDir + filename};
        if (!file)
        {
            throw std::runtime_error("Can't read graph in '" + filename + "' because the file can't be opened!");
        }

        std::string line{"c"};
        while (file && line[0] != 'p')
        {
            std::getline(file, line);
        }

        std::vector<std::string> tokens = tokenize(line);
        int nbVertices{convertToInt(tokens[2])};
        int nbEdges{convertToInt(tokens[3])};

        std::vector<std::vector<DataStructures::VertexType>> adjacencyList(nbVertices);

        std::getline(file, line);
        tokens = tokenize(line);
        while (file)
        {
            if (!(tokens.empty() || tokens[0] == "c"))
            {
                int vertex1{convertToInt(tokens[0])-1};
                int vertex2{convertToInt(tokens[1])-1};
                adjacencyList[vertex1].push_back(vertex2);
                adjacencyList[vertex2].push_back(vertex1);
            }
            std::getline(file, line);
            tokens = tokenize(line);
        }

        return DataStructures::Graph{static_cast<size_t>(nbVertices), adjacencyList};
    }

    std::vector<std::string> Reader::tokenize(std::string& line)
    {
        std::vector<std::string> tokens;
        std::istringstream iss(line);
        copy(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             back_inserter(tokens));
        return tokens;
    }

    int Reader::convertToInt(std::string& str)
    {
        int num;
        std::stringstream ss;
        ss << str;
        ss >> num;
        return num;
    }
}
