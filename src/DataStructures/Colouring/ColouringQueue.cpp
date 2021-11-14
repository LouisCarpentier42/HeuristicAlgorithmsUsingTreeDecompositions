//
// Created by louis on 14/11/2021.
//

#include "ColouringQueue.h"

#include <algorithm>

DataStructures::ColouringQueue::ColouringQueue(size_t nbColourings, const DataStructures::ColouringEvaluator& comparator)
    : nbColourings{nbColourings}, evaluator{comparator}
{}

DataStructures::ColouringQueue::~ColouringQueue()
{
    for (DataStructures::MutableColouring* colouring : queue)
        delete colouring;
}

void DataStructures::ColouringQueue::push(DataStructures::MutableColouring* colouring)
{
    queue.push_back(colouring); // TODO check if the colouring is already in the queue
    if (queue.size() > nbColourings)
    {
        auto it = std::min_element(queue.begin(), queue.end(),
                                   [this](auto* c1, auto* c2){return evaluator(c1, c2);});
        delete *it;
        queue.erase(it);
    }
}

bool DataStructures::ColouringQueue::isEmpty() const
{
    return queue.empty();
}

DataStructures::MutableColouring *DataStructures::ColouringQueue::retrieveBestColouring() const
{
    return *std::max_element(queue.begin(), queue.end(),
                             [this](auto* c1, auto* c2){return evaluator(c1, c2);});
}

DataStructures::ColouringQueue::Iterator DataStructures::ColouringQueue::begin()
{
    return queue.begin();
}

DataStructures::ColouringQueue::Iterator DataStructures::ColouringQueue::end()
{
    return queue.end();
}
