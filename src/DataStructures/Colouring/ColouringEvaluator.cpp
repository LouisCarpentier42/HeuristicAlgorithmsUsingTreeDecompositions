//
// Created by louis on 14/11/2021.
//

#include "ColouringEvaluator.h" // TODO remove if not needed

//DataStructures::ColouringEvaluator::ColouringEvaluator(const DataStructures::Graph* graph)
//    : graph{graph}
//{}

bool DataStructures::ColouringEvaluator::compare(
        const DataStructures::Graph* graph,
        const DataStructures::Colouring* c1,
        const DataStructures::Colouring* c2) const
{
    return evaluate(graph, c1) < evaluate(graph, c2);
}
