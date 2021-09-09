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


namespace TreeDecomposition {

    std::vector<std::string> tokenize(std::string& line)
    {
        std::vector<std::string> tokens;
        std::istringstream iss(line);
        copy(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             back_inserter(tokens));
        return tokens;
    }

    int convertToInt(std::string& str)
    {
        int num;
        std::stringstream ss;
        ss << str;
        ss >> num;
        return num;
    }

    Bag* read(std::string& fileName)
    {
        std::ifstream file{"../TreeDecompositionFiles/" + fileName};
        if (!file)
        {
            throw std::runtime_error("Can't read tree decomposition in '" + fileName + "' because the file can't be opened!");
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
        std::vector<Bag*> bags(nbBags);

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
                bags[bagId-1] = new Bag{bagId, bagSize, vertices};
            }
            std::getline(file, line);
            tokens = tokenize(line);
        }


        while (file) {
            if (!(tokens.empty() || tokens[0] == "c")){
                Bag* firstBag = bags[convertToInt(tokens[0])-1];
                Bag* secondBag = bags[convertToInt(tokens[1])-1];

                firstBag->addChild(secondBag);
            }

            std::getline(file, line);
            tokens = tokenize(line);
        }

        return bags[0]; // TODO maybe find a smarter way to choose a root node?
    }
}

