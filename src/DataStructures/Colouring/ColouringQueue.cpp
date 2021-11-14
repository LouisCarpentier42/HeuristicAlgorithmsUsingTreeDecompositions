//
// Created by louis on 14/11/2021.
//

#include "ColouringQueue.h"

#include <algorithm>

DataStructures::ColouringQueue::ColouringQueue(size_t nbColourings, const DataStructures::ColouringEvaluator* comparator)
    : nbColourings{nbColourings}, evaluator{comparator}
{}

//DataStructures::ColouringQueue::~ColouringQueue()
//{
//    for (DataStructures::MutableColouring* colouring : queue)
//        delete colouring;
//}

void DataStructures::ColouringQueue::push(DataStructures::MutableColouring* colouring)
{
//    std::cout << "--- BEGIN\n";
//    std::cout << *this;
//    std::cout << "Colouring to add: [" << evaluator->evaluate(colouring) << "] " << *colouring << "\n";
    queue.push_back(colouring); // TODO check if the colouring is already in the queue
    if (queue.size() > nbColourings)
    {
        auto it = std::min_element(queue.begin(), queue.end(),
                                   [this](auto* c1, auto* c2){return (*evaluator)(c1, c2);});
        std::cout << "Deleting [" << evaluator->evaluate(*it) << "] " << **it << "\n";
        delete *it;
        queue.erase(it);
    }
//    std::cout << "--- END\n";
}

bool DataStructures::ColouringQueue::isEmpty() const
{
    return queue.empty();
}

DataStructures::MutableColouring *DataStructures::ColouringQueue::retrieveBestColouring() const
{
    return *std::max_element(queue.begin(), queue.end(),
                             [this](auto* c1, auto* c2){return (*evaluator)(c1, c2);});
}

DataStructures::ColouringQueue::Iterator DataStructures::ColouringQueue::begin() const
{
    return queue.begin();
}

DataStructures::ColouringQueue::Iterator DataStructures::ColouringQueue::end() const
{
    return queue.end();
}

std::ostream &DataStructures::operator<<(std::ostream &out, const DataStructures::ColouringQueue &colouringQueue)
{
    out << "COLOURING QUEUE [" << colouringQueue.queue.size() << "]\n";
    for (DataStructures::MutableColouring* colouring : colouringQueue)
        std::cout << "[" << colouringQueue.evaluator->evaluate(colouring) << "] " << *colouring << '\n';
    return out;
}
