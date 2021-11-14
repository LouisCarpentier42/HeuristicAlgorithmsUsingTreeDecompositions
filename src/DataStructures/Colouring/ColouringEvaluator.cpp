//
// Created by louis on 14/11/2021.
//

#include "ColouringEvaluator.h"

DataStructures::ColouringEvaluator::ColouringEvaluator(const DataStructures::Graph* graph)
    : graph{graph}
{}

bool DataStructures::ColouringEvaluator::operator()(const DataStructures::Colouring* c1, const DataStructures::Colouring* c2) const
{
    return evaluate(c1) > evaluate(c2);
}
