//
// Created by louis on 01/12/2021.
//

#include "experimentalAnalysis.h"

#include <chrono>


void computeRankingsExactAlgorithm(
        std::map<DataStructures::NiceNode*, Solvers::ExactTreeDecompositionRankingMHV>& rankings,
        DataStructures::NiceNode* node,
        Solvers::ExactTreeDecompositionSolverBase* exactTD)
{
    if (node->isLeaf())
        rankings[node] = exactTD->solveAtNode(node);
    else
    {
        std::vector<Solvers::ExactTreeDecompositionRankingMHV> rankingsChildren{};
        for (auto it{node->beginChildrenIterator()}; it < node->endChildrenIterator(); it++)
        {
            auto* child = dynamic_cast<DataStructures::NiceNode*>(*it);
            computeRankingsExactAlgorithm(rankings, child, exactTD);
            rankingsChildren.push_back(rankings[child]);
        }
        Solvers::ExactTreeDecompositionRankingMHV rankingNode = exactTD->solveAtNode(node, rankingsChildren);
        rankings[node] = rankingNode;
    }
}

void computeComparisonScores(
        std::map<DataStructures::NiceNode*, double>& scores,
        const std::map<DataStructures::NiceNode*, Solvers::ExactTreeDecompositionRankingMHV>& rankings,
        DataStructures::NiceNode* node)
{
    for (auto it{node->beginChildrenIterator()}; it < node->endChildrenIterator(); it++)
        computeComparisonScores(scores, rankings, dynamic_cast<DataStructures::NiceNode*>(*it));

    const Solvers::ExactTreeDecompositionRankingMHV& rankingNode = rankings.at(node);
    DataStructures::DynamicProgrammingTable* table = node->getTable();

    std::vector<int> evaluationsExactRanking{};
    for (const auto& entry : rankingNode)
        evaluationsExactRanking.push_back(entry.second);
    std::sort(evaluationsExactRanking.begin(), evaluationsExactRanking.end());
    std::reverse(evaluationsExactRanking.begin(), evaluationsExactRanking.end());
    int relevantThreshold{evaluationsExactRanking[table->getNbEntries()-1]};
    std::vector<DataStructures::ColourAssignments> allRelevantColourAssignments{};
    for (const auto& entry : rankingNode)
    {
        if (entry.second >= relevantThreshold)
        {
            allRelevantColourAssignments.push_back(entry.first.first);
        }
    }

    std::vector<bool> isRelevant(table->getNbEntries(), false);
    std::vector<int> evaluations(table->getNbEntries());
    int i{0};
    for (DataStructures::TableEntry* entry : *table)
    {
        for (DataStructures::ColourAssignments& relevantColourAssignment : allRelevantColourAssignments)
        {
            // TODO somehow look at all colours for deciding if it is relevant or not
            bool currentColourAssignmentIsRelevant{true};
            for (DataStructures::VertexType vertex : node->getBagContent())
            {
                if (relevantColourAssignment.getColour(vertex) != entry->getColourAssignments()->getColour(vertex))
                {
                    currentColourAssignmentIsRelevant = false;
                    break;
                }
            }
            if (currentColourAssignmentIsRelevant)
            {
                isRelevant[i] = true;
                break;
            }
        }
        evaluations[i] = entry->getEvaluation();
        i++;
    }

    double accuracy{0.0};
    double nbRelevant{0.0};
    for (int j{0}; j < table->getNbEntries(); j++)
    {
        if (!isRelevant[j]) continue;
        nbRelevant += 1.0;
        double nbElementsBetter{0.0};
        double nbRelevantBetter{0.0};
        for (int k{0}; k < table->getNbEntries(); k++)
        {
            if (evaluations[j] >= evaluations[k])
            {
                nbElementsBetter += 1.0;
                if (isRelevant[k])
                    nbRelevantBetter += 1.0;
            }
        }
        if (nbElementsBetter > 0)
            accuracy += (nbRelevantBetter/nbElementsBetter);
    }
    if (nbRelevant > 0)
        scores[node] = (accuracy/nbRelevant);
}

std::map<std::string, std::map<DataStructures::NiceNode*, double>> compareHeuristicTDsWithExactTD(
        DataStructures::NiceTreeDecomposition* treeDecomposition,
        DataStructures::Graph* graph,
        Solvers::ExactTreeDecompositionSolverBase* exactTD,
        const std::map<std::string, Solvers::HeuristicTreeDecompositionSolver*>& treeDecompositionSolvers)
{
    std::map<DataStructures::NiceNode*, Solvers::ExactTreeDecompositionRankingMHV> rankingsExactAlgorithm{};
    exactTD->setProperties(graph);
    computeRankingsExactAlgorithm(rankingsExactAlgorithm, treeDecomposition->getRoot(), exactTD);

    std::map<std::string, std::map<DataStructures::NiceNode*, double>> results;
    for (auto const& [name, heuristicSolver] : treeDecompositionSolvers)
    {
        graph->removeColours();
        heuristicSolver->solve(graph, treeDecomposition);
        std::map<DataStructures::NiceNode*, double> scores{};
        computeComparisonScores(scores, rankingsExactAlgorithm, treeDecomposition->getRoot());
        results[name] = scores;
    }
    return results;
}

void ExperimentalAnalysis::executeExperiment(IO::Reader& reader, Experiment& experiment)
{
    std::string treeDecompositionResultsDir = experiment.resultFileName + "_accuracies/";
    if (experiment.exactTreeDecompositionSolver != nullptr && std::any_of(experiment.testInstances.begin(), experiment.testInstances.end(), [](auto instance){return instance.compareExactTD; }))
    {
        IO::Reader::createDirectory(treeDecompositionResultsDir);
    }
    std::ofstream resultFile;
    resultFile.open(experiment.resultFileName + ".csv");
    resultFile << "Solver name,graph name,tree decomposition name,initial colouring name,";
    for (int i{0}; i < experiment.nbRepetitionsPerInstance; i++)
        resultFile << "evaluation run " << (i+1) << ",time (µs) run " << (i+1) << ",";
    resultFile << "mean evaluation,mean time(µs)";

    size_t maxNbColours{0};
    for (const auto& instance : experiment.testInstances)
    {
        if (instance.graph->getNbColours() > maxNbColours)
            maxNbColours = instance.graph->getNbColours();
    }
    for (DataStructures::ColourType colour{1}; colour <= maxNbColours; colour++)
        resultFile << ",% colour " << colour;
    resultFile << "\n";

    std::map<std::string, std::ofstream> accuracyFiles;

    for (const TestInstance& testInstance : experiment.testInstances)
    {

        std::cout << "Experimental analysis: solving graph '" << testInstance.graphName << "' with tree decomposition '" << testInstance.treeDecompositionName << "'\n";

        // Test the baselines
        for (auto const& [name, baseline] : experiment.baselines)
        {
            resultFile << name << "," << testInstance.graphName << "," << testInstance.treeDecompositionName << "," << testInstance.colourGeneration << ",";
            std::chrono::microseconds duration{0};
            int evaluation{0};
            std::vector<int> nbVerticesInColour(testInstance.graph->getNbColours());
            for (int repetition{0}; repetition < experiment.nbRepetitionsPerInstance; repetition++)
            {
                testInstance.graph->removeColours();
                auto start = std::chrono::high_resolution_clock::now();
                baseline->solve(testInstance.graph);
                auto stop = std::chrono::high_resolution_clock::now();
                int newEvaluation{experiment.evaluator->evaluate(testInstance.graph)};
                evaluation += newEvaluation;
                duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                for (DataStructures::VertexType vertex{0}; vertex < testInstance.graph->getNbVertices(); vertex++)
                    nbVerticesInColour[testInstance.graph->getColour(vertex) - 1]++;
                resultFile << newEvaluation << "," << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << ",";
            }
            resultFile << evaluation/experiment.nbRepetitionsPerInstance << "," << duration.count()/experiment.nbRepetitionsPerInstance;
            for (int count : nbVerticesInColour)
                resultFile << "," << (double)count / (double)(testInstance.graph->getNbVertices() * experiment.nbRepetitionsPerInstance);
            for (size_t i{testInstance.graph->getNbColours()}; i < maxNbColours; i++)
                resultFile << ",/";
            resultFile << "\n";
        }

        // Test the tree decomposition solvers
        if (!experiment.treeDecompositionSolvers.empty())
        {

            DataStructures::NiceTreeDecomposition niceTreeDecomposition = reader.readNiceTreeDecomposition(testInstance.treeDecompositionName);


            for (auto const& [name, solver] : experiment.treeDecompositionSolvers)
            {
                resultFile << name << "," << testInstance.graphName << "," << testInstance.treeDecompositionName << "," << testInstance.colourGeneration << ",";
                std::chrono::microseconds duration{0};
                int evaluation{0};
                std::vector<int> nbVerticesInColour(testInstance.graph->getNbColours());
                for (int repetition{0}; repetition < experiment.nbRepetitionsPerInstance; repetition++)
                {
                    testInstance.graph->removeColours();
                    auto start = std::chrono::high_resolution_clock::now();
                    solver->solve(testInstance.graph, &niceTreeDecomposition);
                    auto stop = std::chrono::high_resolution_clock::now();
                    int newEvaluation{experiment.evaluator->evaluate(testInstance.graph)};
                    evaluation += newEvaluation;
                    duration += std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                    for (DataStructures::VertexType vertex{0}; vertex < testInstance.graph->getNbVertices(); vertex++)
                        nbVerticesInColour[testInstance.graph->getColour(vertex) - 1]++;
                    resultFile << newEvaluation << "," << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << ",";
                }
                resultFile << evaluation/experiment.nbRepetitionsPerInstance << "," << duration.count()/experiment.nbRepetitionsPerInstance;
                for (int count : nbVerticesInColour)
                    resultFile << "," << (double)count / (double)(testInstance.graph->getNbVertices() * experiment.nbRepetitionsPerInstance);
                for (size_t i{testInstance.graph->getNbColours()}; i < maxNbColours; i++)
                    resultFile << ",/";
                resultFile << "\n";
            }

            if (experiment.exactTreeDecompositionSolver != nullptr && testInstance.compareExactTD)
            {
                int treeHeight{niceTreeDecomposition.getRoot()->getHeight()};
                if (accuracyFiles.find(testInstance.treeDecompositionName) == accuracyFiles.end())
                {
                    accuracyFiles[testInstance.treeDecompositionName] = std::ofstream{};
                    std::string fileName{testInstance.treeDecompositionName.substr(0, testInstance.treeDecompositionName.size()-3) + ".csv"};
                    std::replace(fileName.begin(), fileName.end(), '/', '-');
                    accuracyFiles[testInstance.treeDecompositionName].open(treeDecompositionResultsDir + fileName);
                    accuracyFiles[testInstance.treeDecompositionName] << "Solver name,graph name,initial colouring name,";

                    accuracyFiles[testInstance.treeDecompositionName] << "MAP,";
                    accuracyFiles[testInstance.treeDecompositionName] << "MAP leaf,MAP introduce,MAP forget,MAP join,";
                    for (int h{0}; h < treeHeight; h++)
                        accuracyFiles[testInstance.treeDecompositionName] << "MAP height " << h << ",";
                    accuracyFiles[testInstance.treeDecompositionName] << "MAP height " << treeHeight << "\n";
                }

                std::ofstream& file = accuracyFiles[testInstance.treeDecompositionName];

                std::map<std::string, std::map<DataStructures::NiceNode*, double>> results =
                        compareHeuristicTDsWithExactTD(&niceTreeDecomposition, testInstance.graph, experiment.exactTreeDecompositionSolver, experiment.treeDecompositionSolvers);

                for (auto const& [algorithm, accuracies] : results)
                {
                    file << algorithm << "," << testInstance.graphName << "," << testInstance.colourGeneration << ",";
                    double totalAccuracy{0};
                    int totalNbNodes{0};
                    std::vector<double> accuracyAtHeight(treeHeight+1, 0.0);
                    std::vector<int> nbNodesAtHeight(treeHeight+1, 0);
                    std::vector<double> accuracyForType(4, 0.0);
                    std::vector<int> nbNodesForType(4, 0);
                    for (auto const& [node, accuracy] : accuracies)
                    {
                        totalAccuracy += accuracy;
                        totalNbNodes += 1;
                        int nodeHeight{node->getHeight()};
                        accuracyAtHeight[nodeHeight] += accuracy;
                        nbNodesAtHeight[nodeHeight] += 1;
                        int indexNodeType;
                        switch (node->getNodeType())
                        {
                            case DataStructures::NodeType::LeafNode: indexNodeType = 0; break;
                            case DataStructures::NodeType::ForgetNode: indexNodeType = 1; break;
                            case DataStructures::NodeType::IntroduceNode: indexNodeType = 2; break;
                            case DataStructures::NodeType::JoinNode: indexNodeType = 3; break;
                        }
                        accuracyForType[indexNodeType] += accuracy;
                        nbNodesForType[indexNodeType] += 1;
                    }
                    file << (totalAccuracy / totalNbNodes) << ",";
                    for (int i{0}; i < 4; i++)
                        file << (accuracyForType[i] / nbNodesForType[i]) << ",";

                    for (int h{0}; h < treeHeight; h++)
                        file << (accuracyAtHeight[h] / nbNodesAtHeight[h]) << ",";
                    file << (accuracyAtHeight[treeHeight] / nbNodesAtHeight[treeHeight]) << "\n";
                }
            }

            if (experiment.exactTreeDecompositionSolver != nullptr && testInstance.executeExactTD)
            {
                resultFile << "exact-td," << testInstance.graphName << "," << testInstance.treeDecompositionName << "," << testInstance.colourGeneration << ",";
                auto start = std::chrono::high_resolution_clock::now();
                int evaluation = experiment.exactTreeDecompositionSolver->solve(testInstance.graph, &niceTreeDecomposition);
                auto stop = std::chrono::high_resolution_clock::now();
                for (int i{0}; i < experiment.nbRepetitionsPerInstance; i++) resultFile << ",,";
                resultFile << evaluation << "," << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "\n";
            }
        }
    }

    resultFile.close();
    for (auto& [treeDecompositionName, file] : accuracyFiles)
        file.close();
}
