//
// Created by louis on 11/02/2022.
//

#include "Reader.h"

#include "../Solvers/HeuristicTreeDecompositionSolver/LeafNodeHandler/ConcreteLeafNodeHandlers.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/IntroduceNodeHandler/ConcreteIntroduceNodeHandlers.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/ForgetNodeHandler/ConcreteForgetNodeHandlers.h"
#include "../Solvers/HeuristicTreeDecompositionSolver/JoinNodeHandler/ConcreteJoinNodeHandlers.h"
#include "../DataStructures/Evaluator/PotentialHappyColouredMHVEvaluator.h"
#include "../DataStructures/Evaluator/PotentialHappyUncolouredMHVEvaluator.h"

#include <random>

const DataStructures::Evaluator* IO::Reader::readEvaluator(const std::string& str)
{
    std::vector<std::string> parameters = splitParameters(str);
    if (parameters[0] == "basicMHVEvaluator")
        return new DataStructures::BasicMHVEvaluator{};
    else if (parameters[0] == "colouredMHVEvaluator")
        return new DataStructures::PotentialHappyColouredMHVEvaluator{
        IO::Reader::convertToInt(parameters[1]),
        IO::Reader::convertToInt(parameters[2]),
        IO::Reader::convertToInt(parameters[3])
    };
    else if (parameters[0] == "uncolouredMHVEvaluator")
        return new DataStructures::PotentialHappyUncolouredMHVEvaluator{
        IO::Reader::convertToInt(parameters[1]),
        IO::Reader::convertToInt(parameters[2]),
        IO::Reader::convertToInt(parameters[3]),
        IO::Reader::convertToInt(parameters[4]),
        IO::Reader::convertToInt(parameters[5]),
        IO::Reader::convertToInt(parameters[6])
    };
    throw std::runtime_error("Invalid evaluator identifier is given: " + str + "!");
}

Solvers::LeafNodeHandler* IO::Reader::readLeafNodeHandler(const std::string& str)
{
    if (str == "passive")
        return new Solvers::PassiveLeafNodeHandlers{};
    throw std::runtime_error("Invalid leaf node handler identifier is given: " + str + "!");
}

Solvers::IntroduceNodeHandler* IO::Reader::readIntroduceNodeHandler(const std::string& str)
{
    if (str == "bestColour")
        return new Solvers::BestColourIntroduceNodeHandler{};
    else if (str == "greedy")
        return new Solvers::GreedyIntroduceNodeHandler{};
    throw std::runtime_error("Invalid introduce node handler identifier is given: " + str + "!");
}

Solvers::ForgetNodeHandler* IO::Reader::readForgetNodeHandler(const std::string& str)
{
    if (str == "passive")
        return new Solvers::PassiveForgetNodeHandler{};
    throw std::runtime_error("Invalid forget node handler identifier is given: " + str + "!");
}

Solvers::JoinNodeHandler* IO::Reader::readJoinNodeHandler(const std::string& str)
{
    std::vector<std::string> parameters = splitParameters(str);
    if (parameters[0] == "staticOrder")
    {
        if (parameters[1] == "default")
            return new Solvers::StaticOrderJoinNodeHandler{getEvaluationMerger(parameters[2]), Solvers::StaticOrderJoinNodeHandler::Order::defaultOrder};
        else if (parameters[1] == "gdf")
            return new Solvers::StaticOrderJoinNodeHandler{getEvaluationMerger(parameters[2]), Solvers::StaticOrderJoinNodeHandler::Order::greatestDegreeFirst};
        else if (parameters[1] == "sdf")
            return new Solvers::StaticOrderJoinNodeHandler{getEvaluationMerger(parameters[2]), Solvers::StaticOrderJoinNodeHandler::Order::smallestDegreeFirst};
        else if (parameters[1] == "random")
            return new Solvers::StaticOrderJoinNodeHandler{getEvaluationMerger(parameters[2]), Solvers::StaticOrderJoinNodeHandler::Order::random};
    }
    else if (parameters[0] == "dynamicOrder")
    {
        if (parameters[1] == "mostColouredNeighbours")
            return new Solvers::DynamicOrderJoinNodeHandler{getEvaluationMerger(parameters[2]), Solvers::DynamicOrderJoinNodeHandler::Order::mostColouredNeighboursFirst};
        else if (parameters[1] == "DynamicOrderJoinNodeHandler")
            return new Solvers::DynamicOrderJoinNodeHandler{getEvaluationMerger(parameters[2]), Solvers::DynamicOrderJoinNodeHandler::Order::fewestColouredNeighboursFirst};
        else if (parameters[1] == "mostPotentialHappyNeighbours")
            return new Solvers::DynamicOrderJoinNodeHandler{getEvaluationMerger(parameters[2]), Solvers::DynamicOrderJoinNodeHandler::Order::mostPotentialHappyNeighbours};
        else if (parameters[1] == "mostPercentPotentialHappyNeighbours")
            return new Solvers::DynamicOrderJoinNodeHandler{getEvaluationMerger(parameters[2]), Solvers::DynamicOrderJoinNodeHandler::Order::mostPercentPotentialHappyNeighbours};
    }
    else if (parameters[0] == "greedyColourBag")
    {
        return new Solvers::GreedyColourBagJoinNodeHandler{getEvaluationMerger(parameters[1])};
    }
    else if (parameters[0] == "growthColourBag")
    {
        return new Solvers::GrowthColourBagJoinNodeHandler{getEvaluationMerger(parameters[1])};
    }
    else if (parameters[0] == "useChildColours")
    {
        return new Solvers::UseChildColoursJoinNodeHandler{getEvaluationMerger(parameters[1])};
    }

    throw std::runtime_error("Invalid join node handler identifier is given: " + str + "!");
}

Solvers::EvaluationMerger* IO::Reader::getEvaluationMerger(const std::string& str)
{
    if (str == "avg")
        return new Solvers::AverageEvaluationMerger{};
    else if (str == "max")
        return new Solvers::MaximumEvaluationMerger{};
    else if (str == "min")
        return new Solvers::MinimumEvaluationMerger{};

    throw std::runtime_error("Invalid evaluation merger identifier is given: " + str + "!");
}

std::map<std::string, std::vector<DataStructures::ColourType>> IO::Reader::readColouringString(const std::string& str, const DataStructures::Graph* graph)
{
    std::vector<std::string> parameters = splitParameters(str);
    if (parameters[0] == "random")
    {
        int nbColours{IO::Reader::convertToInt(parameters[1])};
        double percentColouredVertices{std::stod(parameters[2])};
        int nbColourings{IO::Reader::convertToInt(parameters[3])};
        unsigned int seed{parameters.size() <= 4
        ? std::random_device{}()
        : IO::Reader::convertToInt(parameters[4])};
        static std::mt19937 rng{seed};
        std::map<std::string, std::vector<DataStructures::ColourType>> colourings{};
        for (int j{0}; j < nbColourings; j++)
        {
            std::uniform_int_distribution<DataStructures::ColourType> colourDistribution(1, nbColours);

            // Create a random shuffling of the vertices and colour them in this order
            std::vector<DataStructures::VertexType> allVertices(graph->getNbVertices());
            std::iota(allVertices.begin(), allVertices.end(), 0);
            std::shuffle(allVertices.begin(), allVertices.end(), rng);

            // Colour the first nbColours vertices in each colour before randomly colour the remaining vertices
            std::vector<DataStructures::ColourType> colourVector(graph->getNbVertices());
            for (int i{0}; i < nbColours; i++)
                colourVector[allVertices[i]] = i+1;
            size_t nbVerticesToColour{static_cast<size_t>(percentColouredVertices * static_cast<double>(graph->getNbVertices()))};
            for (int i{nbColours}; i < nbVerticesToColour; i++)
                colourVector[allVertices[i]] = colourDistribution(rng);
            colourings["random(nbColours:" + std::to_string(nbColours) + ";" +
            "%colouredVertices:" + std::to_string(percentColouredVertices) + ";" +
            "generated:[" + std::to_string(j+1) + "/" + std::to_string(nbColourings) + "];" +
            "seed:" + std::to_string(seed) + ")"] = colourVector;
        }
        return colourings;
    }

    throw std::runtime_error("Invalid colouring identifier is given: " + str + "!");
}

