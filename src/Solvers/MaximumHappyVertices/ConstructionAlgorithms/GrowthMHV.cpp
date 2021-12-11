//
// Created by louis on 27/10/2021.
//

#include "GrowthMHV.h"

#include <algorithm>
#include <set>
#include <numeric>

static std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> vertexTypes{};
static std::set<DataStructures::VertexType> H_vertices{};
static std::set<DataStructures::VertexType> U_vertices{};
static std::set<DataStructures::VertexType> P_vertices{};
static std::set<DataStructures::VertexType> LP_vertices{};
static std::set<DataStructures::VertexType> LH_vertices{};
static std::set<DataStructures::VertexType> LU_vertices{};
static std::set<DataStructures::VertexType> LF_vertices{};


void printType(DataStructures::VertexType vertex) {
    switch (vertexTypes[vertex])
    {
        case MaximumHappyVertices::GrowthMHV::GrowthType::TEMP_INVALID_TYPE:
            std::cout << "temp "; break;
        case MaximumHappyVertices::GrowthMHV::GrowthType::H_vertex:
            std::cout << "h ";break;
        case MaximumHappyVertices::GrowthMHV::GrowthType::U_vertex:
            std::cout << "u ";break;
        case MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex:
            std::cout << "p ";break;
        case MaximumHappyVertices::GrowthMHV::GrowthType::LH_vertex:
            std::cout << "lh ";break;
        case MaximumHappyVertices::GrowthMHV::GrowthType::LU_vertex:
            std::cout << "lu ";break;
        case MaximumHappyVertices::GrowthMHV::GrowthType::LP_vertex:
            std::cout << "lp ";break;
        case MaximumHappyVertices::GrowthMHV::GrowthType::LF_vertex:
            std::cout << "lf ";break;
    }
}

void testTypes(const DataStructures::Graph* graph,
               const DataStructures::Colouring* colouring)
{


    for (DataStructures::VertexType vertex : H_vertices)
    {
        if (!colouring->isColoured(vertex))
        {
            std::cout << "H VERTEX IS NOT COLOURED!\n";
            break;
        }

        std::set<DataStructures::ColourType> nc_not_coloured{};
        std::set<DataStructures::ColourType> nc_coloured{};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (colouring->isColoured(neighbour))
                nc_coloured.insert(colouring->getColour(neighbour));
            else
                nc_not_coloured.insert(colouring->getColour(neighbour));
        }

        if (nc_coloured.size() != 1)
        {
            std::cout << "H VERTEX HAS NOT A SINGLE COLOUR FOR NEIGHBOURS\n";
            break;
        }

        if (*nc_coloured.begin() != colouring->getColour(vertex))
        {
            std::cout << "COLOURS NEIGHBOURS H VERTEX DIFFERENT\n";
            break;
        }

        if (!nc_not_coloured.empty())
        {
            std::cout << "H VERTEX HAS NOT COLOURED NEIGHBOURS\n";
            break;
        }
    }

    for (DataStructures::VertexType vertex : U_vertices)
    {
        if (!colouring->isColoured(vertex))
        {
            std::cout << "u VERTEX IS NOT COLOURED!\n";
            break;
        }

        std::set<DataStructures::ColourType> nc_not_coloured{};
        std::set<DataStructures::ColourType> nc_coloured{};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (colouring->isColoured(neighbour))
                nc_coloured.insert(colouring->getColour(neighbour));
            else
                nc_not_coloured.insert(colouring->getColour(neighbour));
        }

        //        if (!nc_not_coloured.empty())
        //        {
        //            std::cout << "U VERTEX HAS NOT COLOURED NEIGHBOURS\n";
        //            break;
        //        }

        if (nc_coloured.size() == 1 && *nc_coloured.begin() == colouring->getColour(vertex))
        {
            std::cout << "U VERTEX AND NEIGHBOURS ALL SAME COLOUR\n";
            break;
        }
    }

    for (DataStructures::VertexType vertex : P_vertices)
    {
        if (!colouring->isColoured(vertex))
        {
            std::cout << "P VERTEX NOT COLOURED!\n";
            break;
        }

        std::set<DataStructures::ColourType> nc_not_coloured{};
        std::set<DataStructures::ColourType> nc_coloured{};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (colouring->isColoured(neighbour))
                nc_coloured.insert(colouring->getColour(neighbour));
            else
                nc_not_coloured.insert(colouring->getColour(neighbour));
        }

        //        if (nc_coloured.empty())
        //        {
        //            std::cout << "P VERTEX NO COLOURED NEIGHBOUR!\n";
        //            break;
        //        }

        //        if (!nc_not_coloured.empty())
        //        {
        //            std::cout << "P VERTEX NO UNCOLOURED NEIGHBOUR!\n";
        //            break;
        //        }

        if (nc_not_coloured.size() > 1)
        {
            std::cout << "P MORE THAN 1 COLOUR NEIGHBOUR!\n";
            break;
        }

    }

    for (DataStructures::VertexType vertex : LP_vertices)
    {
        if (colouring->isColoured(vertex))
        {
            std::cout << "LP VERTEX COLOURED!\n";
            break;
        }

        bool hasPNeighbour{false};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (vertexTypes[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex)
            {
                hasPNeighbour = true;
                break;
            }
        }

        if (!hasPNeighbour) std::cout << "ERROR WITH LP VERTICES!\n";
    }

    for (DataStructures::VertexType vertex : LH_vertices)
    {
        if (colouring->isColoured(vertex))
        {
            std::cout << "LH VERTEX COLOURED!\n";
            break;
        }

        bool hasPNeighbour{false};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (vertexTypes[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex)
            {
                hasPNeighbour = true;
                break;
            }
        }

        if (hasPNeighbour) std::cout << "LH vertex has P neighbour!\n";

        std::set<DataStructures::ColourType> nc_not_coloured{};
        std::set<DataStructures::ColourType> nc_coloured{};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (colouring->isColoured(neighbour))
                nc_coloured.insert(colouring->getColour(neighbour));
            else
                nc_not_coloured.insert(colouring->getColour(neighbour));
        }

        if (nc_coloured.empty())
        {
            std::cout << "LH has no coloured neighbours!\n";
        }

        if (nc_coloured.size() != 1)
        {
            std::cout << "LH does not have one colour of neighbours!\n";
        }
    }

    for (DataStructures::VertexType vertex : LU_vertices)
    {
        if (colouring->isColoured(vertex))
        {
            std::cout << "ERROR WITH LU VERTICES!\n";
            break;
        }

        bool hasPNeighbour{false};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (vertexTypes[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex)
            {
                std::cout << "DSQFHILSQDMJFQLMKSDFJDALKFJZDMLFJ!\n";
                hasPNeighbour = true;
                break;
            }
        }

        if (hasPNeighbour) std::cout << "LU vertex has P neighbour!\n";

        std::set<DataStructures::ColourType> nc_not_coloured{};
        std::set<DataStructures::ColourType> nc_coloured{};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (colouring->isColoured(neighbour))
                nc_coloured.insert(colouring->getColour(neighbour));
            else
                nc_not_coloured.insert(colouring->getColour(neighbour));
        }

        if (nc_coloured.empty())
        {
            std::cout << "LU has no coloured neighbours!\n";
        }

        if (nc_coloured.size() == 1)
        {
            std::cout << "LU has only one coloured neighbour!\n";
        }
    }

    for (DataStructures::VertexType vertex : LF_vertices)
    {
        if (colouring->isColoured(vertex))
        {
            std::cout << "ERROR WITH LF VERTICES!\n";
            break;
        }

        std::set<DataStructures::ColourType> nc_not_coloured{};
        std::set<DataStructures::ColourType> nc_coloured{};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (colouring->isColoured(neighbour))
                nc_coloured.insert(colouring->getColour(neighbour));
            else
                nc_not_coloured.insert(colouring->getColour(neighbour));
        }

        if (!nc_coloured.empty())
        {
            std::cout << "LF has coloured neighbour!\n";
            if (std::any_of(graph->getNeighbours(vertex)->begin(), graph->getNeighbours(vertex)->begin(),
                            [colouring](auto n){return colouring->isColoured(n);}))
            {
                std::cout << "WOOPS2\n";
            }
        }
    }
}

DataStructures::Colouring* MaximumHappyVertices::GrowthMHV::solve(
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring) const
{
    vertexTypes.clear();
    vertexTypes.resize(graph->getNbVertices());
    H_vertices.clear();
    U_vertices.clear();
    P_vertices.clear();
    LP_vertices.clear();
    LH_vertices.clear();
    LU_vertices.clear();
    LF_vertices.clear();

    std::deque<DataStructures::VertexType> verticesToUpdate(graph->getNbVertices());
    std::iota(verticesToUpdate.begin(), verticesToUpdate.end(), 0);
    setGrowthTypes(verticesToUpdate, graph, colouring);

    auto* solution = new DataStructures::MutableColouring{colouring};
    while (!(LP_vertices.empty() && LH_vertices.empty() && LU_vertices.empty() && LF_vertices.empty()))
    {
        std::cout << "--------------------------------------------------\n";
        if (!P_vertices.empty())
        {
            auto vertexIt{P_vertices.begin()};
            std::cout << "P VERTEX: " << *vertexIt << "\n";
            DataStructures::ColourType colour{solution->getColour(*vertexIt)};
            std::cout << "COLOURING: ";
            for (DataStructures::VertexType neighbour : *graph->getNeighbours(*vertexIt))
            {
                if (vertexTypes[neighbour] == GrowthType::LP_vertex)
                {
                    std::cout << neighbour << " ";
                    solution->setColour(neighbour, colour);
                }
            }
            std::cout << "\n";
            verticesToUpdate = verticesAtDistance(3, *vertexIt, graph);
        }
        else if (!LH_vertices.empty())
        {
            auto vertexIt{LH_vertices.begin()};
            std::cout << "LH VERTEX: " << *vertexIt << "\n";
            auto uNeighbourIt = std::find_if(
                graph->getNeighbours(*vertexIt)->begin(),
                graph->getNeighbours(*vertexIt)->end(),
                [](const DataStructures::VertexType& neighbour)
                    { return vertexTypes[neighbour] == GrowthType::U_vertex; }
            );
            DataStructures::ColourType colour{solution->getColour(*uNeighbourIt)};
            solution->setColour(*vertexIt, colour);
            for (DataStructures::VertexType neighbour : *graph->getNeighbours(*vertexIt))
            {
                if (!solution->isColoured(neighbour))
                {
                    solution->setColour(neighbour, colour);
                }
            }
            verticesToUpdate = verticesAtDistance(3, *vertexIt, graph);
        }
        else if (!LU_vertices.empty())
        {
            auto vertexIt{LU_vertices.begin()};
            std::cout << "LU VERTEX: " << *vertexIt << "\n";
            auto uNeighbourIt = std::find_if(
                graph->getNeighbours(*vertexIt)->begin(),
                graph->getNeighbours(*vertexIt)->end(),
                [](const DataStructures::VertexType& neighbour)
                    { return vertexTypes[neighbour] == GrowthType::U_vertex; }
            );
            solution->setColour(*vertexIt, solution->getColour(*uNeighbourIt));

            verticesToUpdate.push_back(*vertexIt);
            for (DataStructures::VertexType neighbour : *graph->getNeighbours(*vertexIt))
                verticesToUpdate.push_back(neighbour);
        }
//        else
//        {
//            std::cout << "REACHED-----------------------------------------------------------\n";
//            for (auto v : LF_vertices)
//            {
//                for (DataStructures::VertexType neighbour : *graph->getNeighbours(v))
//                {
//                    if (colouring->isColoured(neighbour))
//                    {
//                        std::cout << "WOOPSSSSSSS LF HAS COLOURED NEIGHBOUR\n";
//                        break;
//                    }
//                }
//            }
//
//            // Only LF vertices remain to be coloured, which means they form (a) disconnected
//            // component(s) and can all receive an arbitrary colour such that all of them are happy
//            for (DataStructures::VertexType lfVertex : LF_vertices)
//                solution->setColour(lfVertex, 1);
//            break;
//        }

        for (DataStructures::VertexType vertex : verticesToUpdate)
        {
            switch (vertexTypes[vertex])
            {

                case GrowthType::H_vertex: H_vertices.erase(vertex); break;
                case GrowthType::U_vertex: U_vertices.erase(vertex); break;
                case GrowthType::P_vertex:
                    std::cout << "REMOVING " << vertex << "\n";
                    P_vertices.erase(vertex);
                    break;
                case GrowthType::LH_vertex: LH_vertices.erase(vertex); break;
                case GrowthType::LU_vertex: LU_vertices.erase(vertex); break;
                case GrowthType::LP_vertex: LP_vertices.erase(vertex); break;
                case GrowthType::LF_vertex: LF_vertices.erase(vertex); break;
                case GrowthType::TEMP_INVALID_TYPE: break;
            }
            vertexTypes[vertex] = GrowthType::TEMP_INVALID_TYPE;
        }
        setGrowthTypes(verticesToUpdate, graph, solution);
    }
    return solution;
}

void MaximumHappyVertices::GrowthMHV::setGrowthTypes(
        std::deque<DataStructures::VertexType>& verticesToUpdate,
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* colouring)
{

    std::cout << *colouring << '\n';
    std::deque<DataStructures::VertexType> colouredVerticesToUpdate{};
    std::deque<DataStructures::VertexType> uncolouredVerticesToUpdate{};
    while (!verticesToUpdate.empty())
    {
        DataStructures::VertexType vertex{verticesToUpdate.front()};
        verticesToUpdate.pop_front();
        if (colouring->isColoured(vertex))
            colouredVerticesToUpdate.push_back(vertex);
        else
            uncolouredVerticesToUpdate.push_back(vertex);

        std::cout << vertex << " ";
    }
    std::cout << "\n";

    while (!colouredVerticesToUpdate.empty())
    {
        DataStructures::VertexType vertex{colouredVerticesToUpdate.front()};
        colouredVerticesToUpdate.pop_front();

        bool vertexIsUnhappy{false};
        bool hasUncolouredNeighbour{false};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (!colouring->isColoured(neighbour))
            {
                hasUncolouredNeighbour = true;
            }
            else if (colouring->getColour(neighbour) != colouring->getColour(vertex))
            {
                vertexIsUnhappy = true;
                break;
            }
        }

        if (vertexIsUnhappy)
        {
            U_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::U_vertex;
            std::cout << "U VERTEX " << vertex << ", " << colouring->getColour(vertex) << ": ";
            for (auto n : *graph->getNeighbours(vertex))
            {
                std::cout << "[" << n << ", " << colouring->getColour(n) << "] ";
            }
            std::cout << "\n";
        }
        else if (hasUncolouredNeighbour)
        {
            P_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::P_vertex;
            std::cout << "P VERTEX " << vertex << ", " << colouring->getColour(vertex) << ": ";
            for (auto n : *graph->getNeighbours(vertex))
            {
                std::cout << "[" << n << ", " << colouring->getColour(n) << "] ";
            }
            std::cout << "\n";
        }
        else
        {
            H_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::H_vertex;
            std::cout << "H VERTEX " << vertex << ", " << colouring->getColour(vertex) << ": ";
            for (auto n : *graph->getNeighbours(vertex))
            {
                std::cout << "[" << n << ", " << colouring->getColour(n) << "] ";
            }
            std::cout << "\n";
        }
    }

    while (!uncolouredVerticesToUpdate.empty())
    {
        DataStructures::VertexType vertex{uncolouredVerticesToUpdate.front()};
        uncolouredVerticesToUpdate.pop_front();

        DataStructures::ColourType colourNeighbours{0};
        bool hasPNeighbour{false};
        bool isUnhappy{false};
        for (DataStructures::VertexType neighbour : *graph->getNeighbours(vertex))
        {
            if (vertexTypes[neighbour] == GrowthType::P_vertex)
            {
                hasPNeighbour = true;
                break;
            }
            else if (colourNeighbours == 0 && colouring->isColoured(neighbour))
            {
                colourNeighbours = colouring->getColour(neighbour);
            }
            else if (colourNeighbours != 0 && colouring->isColoured(neighbour) && colouring->getColour(neighbour) != colourNeighbours)
            {
                isUnhappy = true;
            }
//            else if (colourNeighbours != 0 && colouring->getColour(neighbour) != colourNeighbours)
//            {
//                isUnhappy = true;
//            }
//            else if (colouring->isColoured(neighbour))
//            {
//                colourNeighbours = colouring->getColour(neighbour);
//            }
        }

        if (hasPNeighbour)
        {
            LP_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::LP_vertex;
        }
        else if (isUnhappy)
        {
            LU_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::LU_vertex;
        }
        else if (colourNeighbours == 0) // No neighbours have a colour
        {
            LF_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::LF_vertex;
        }
        else
        {
            LH_vertices.insert(vertex);
            vertexTypes[vertex] = GrowthType::LH_vertex;
        }
    }

    unsigned int vertex{0};
    std::cout << vertex << ", " << colouring->getColour(vertex) << ": ";
    printType(vertex);
    for (auto n : *graph->getNeighbours(vertex))
    {
        std::cout << "[" << n << ", " << colouring->getColour(n) << "] ";
    }
    std::cout << "\n";

    std::cout << "H vertices: ";
    for (auto v : H_vertices)
        std::cout << v << " ";
    std::cout << '\n';

    std::cout << "P vertices: ";
    for (auto v : P_vertices)
        std::cout << v << " ";
    std::cout << '\n';
}

std::deque<DataStructures::VertexType> MaximumHappyVertices::GrowthMHV::verticesAtDistance(
        size_t distance,
        DataStructures::VertexType vertex,
        const DataStructures::Graph* graph)
{
    // Neighbourhood at distance 1
    std::set<DataStructures::VertexType> neighbourhood{};
    std::set<DataStructures::VertexType> verticesToCheck{vertex};

    // Neighbourhood at distance 2 to distance (distance-1)
    for (size_t currentDistance{1}; currentDistance <= distance; currentDistance++)
    {
        std::set<DataStructures::VertexType> nextVerticesToCheck(neighbourhood);
        for (DataStructures::VertexType vertexToCheck : verticesToCheck)
        {
            auto pair = neighbourhood.insert(vertexToCheck);
            if (pair.second)
            {
                nextVerticesToCheck.insert(
                    graph->getNeighbours(vertexToCheck)->begin(),
                    graph->getNeighbours(vertexToCheck)->end()
                );
            }
        }
        verticesToCheck = nextVerticesToCheck;
    }

    // At the last distance, you don't need to do any computations for neighbouring vertices
    for (DataStructures::VertexType vertexToCheck : verticesToCheck)
        neighbourhood.insert(vertexToCheck);

    return {neighbourhood.begin(), neighbourhood.end()};
}


//// TODO old/unoptimized version
//DataStructures::Colouring* MaximumHappyVertices::GrowthMHV::solve(const DataStructures::Graph* graph, const DataStructures::Colouring* colouring) const
//{
//    std::vector<MaximumHappyVertices::GrowthMHV::GrowthType> types(graph->getNbVertices());
//    auto* solution = new DataStructures::MutableColouring{colouring};
//
//    updateVertexTypes(graph, solution, types);
//
//    while (std::any_of(
//            types.begin(),
//            types.end(),
//            [](MaximumHappyVertices::GrowthMHV::GrowthType type) {
//                return type == MaximumHappyVertices::GrowthMHV::GrowthType::LH_vertex ||
//                        type == MaximumHappyVertices::GrowthMHV::GrowthType::LU_vertex ||
//                       type == MaximumHappyVertices::GrowthMHV::GrowthType::LP_vertex ||
//                       type == MaximumHappyVertices::GrowthMHV::GrowthType::LF_vertex;
//                }
//            ))
//    {
//        auto pVertexIterator = std::find(types.begin(), types.end(), MaximumHappyVertices::GrowthMHV::GrowthType::P_vertex);
//        if (pVertexIterator != types.end())
//        {
//            DataStructures::VertexType pVertex = std::distance(types.begin(), pVertexIterator);
//            for (DataStructures::VertexType neighbour : *graph->getNeighbours(pVertex))
//            {
//                if (types[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::LP_vertex)
//                {
//                    solution->setColour(neighbour, solution->getColour(pVertex));
//                }
//            }
//        }
//        else
//        {
//            auto lhVertexIterator = std::find(types.begin(), types.end(), MaximumHappyVertices::GrowthMHV::GrowthType::LH_vertex);
//            if (lhVertexIterator != types.end())
//            {
//                DataStructures::VertexType lhVertex = std::distance(types.begin(), lhVertexIterator);
//                DataStructures::ColourType uNeighbourColour{0};
//                for (DataStructures::VertexType neighbour : *graph->getNeighbours(lhVertex))
//                {
//                    if (types[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::U_vertex)
//                    {
//                        uNeighbourColour = solution->getColour(neighbour);
//                        break;
//                    }
//                }
//                solution->setColour(lhVertex, uNeighbourColour);
//                for (DataStructures::VertexType neighbour : *graph->getNeighbours(lhVertex))
//                {
//                    if (types[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::LH_vertex ||
//                        types[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::LU_vertex ||
//                        types[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::LP_vertex ||
//                        types[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::LF_vertex)
//                    {
//                        solution->setColour(neighbour, uNeighbourColour);
//                    }
//                }
//            }
//            else // There must be an LU vertex
//            {
//                auto luVertexIterator = std::find(types.begin(), types.end(), MaximumHappyVertices::GrowthMHV::GrowthType::LU_vertex);
//                DataStructures::VertexType luVertex = std::distance(types.begin(), luVertexIterator);
//                for (DataStructures::VertexType neighbour : *graph->getNeighbours(luVertex))
//                {
//                    if (types[neighbour] == MaximumHappyVertices::GrowthMHV::GrowthType::U_vertex)
//                    {
//                        solution->setColour(luVertex, solution->getColour(neighbour));
//                        break;
//                    }
//                }
//            }
//        }
//        updateVertexTypes(graph, solution, types);
//    }
//    return solution;
//}

void MaximumHappyVertices::GrowthMHV::updateVertexTypes(const DataStructures::Graph* graph, const DataStructures::Colouring* colouring, std::vector<GrowthType>& types)
{
    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (colouring->isColoured(vertex))
        {
            // If all of vertex's neighbours have the same colour
            if (std::all_of(
                    graph->getNeighbours(vertex)->begin(),
                    graph->getNeighbours(vertex)->end(),
                    [colouring, vertexColour{colouring->getColour(vertex)}](DataStructures::VertexType neighbour){return colouring->getColour(neighbour) == vertexColour;} ))
                types[vertex] = GrowthType::H_vertex;
            // If any of vertex's neighbours has a different colour
            else if (std::any_of(
                    graph->getNeighbours(vertex)->begin(),
                    graph->getNeighbours(vertex)->end(),
                    [colouring, vertexColour{colouring->getColour(vertex)}](DataStructures::VertexType neighbour){return colouring->isColoured(neighbour) && colouring->getColour(neighbour) != vertexColour;} ))
                types[vertex] = GrowthType::U_vertex;
            // None of vertex's neighbours have a different colour, but not all of them have been coloured in the same colour
            else
                types[vertex] = GrowthType::P_vertex;
        }
    }

    for (DataStructures::VertexType vertex{0}; vertex < graph->getNbVertices(); vertex++)
    {
        if (!colouring->isColoured(vertex))
        {
            if (std::any_of(
                    graph->getNeighbours(vertex)->begin(),
                    graph->getNeighbours(vertex)->end(),
                    [types](DataStructures::VertexType neighbour){return types[neighbour] == GrowthType::P_vertex;} ))
                types[vertex] = GrowthType::LP_vertex;
            else if (std::all_of(
                    graph->getNeighbours(vertex)->begin(),
                    graph->getNeighbours(vertex)->end(),
                    [colouring](DataStructures::VertexType neighbour){return !colouring->isColoured(neighbour);} ))
                types[vertex] = GrowthType::LF_vertex;
            else
            {
                for (int i{0}; i < graph->getDegree(vertex); i++)
                {
                    if (colouring->isColoured((*graph->getNeighbours(vertex))[i]))
                    {
                        // Check if all following neighbours either are not coloured or have the same colour
                        DataStructures::ColourType colour{colouring->getColour((*graph->getNeighbours(vertex))[i])};
                        if (std::all_of(
                                graph->getNeighbours(vertex)->begin()+i,
                                graph->getNeighbours(vertex)->end(),
                                [colouring, colour](DataStructures::VertexType neighbour){return !colouring->isColoured(neighbour) || colouring->getColour(neighbour) == colour;} ))
                            types[vertex] = GrowthType::LH_vertex;
                        else
                            types[vertex] = GrowthType::LU_vertex;
                        break;
                    }
                }
            }
        }
    }
}