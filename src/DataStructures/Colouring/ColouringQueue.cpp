//
// Created by louis on 14/11/2021.
//

#include "ColouringQueue.h"

#include <algorithm>
#include <random>

// TODO optimize (eg with std::set)

DataStructures::ColouringQueue::ColouringQueue(size_t nbColourings, const DataStructures::ColouringEvaluator* comparator)
    : nbColourings{nbColourings}, evaluator{comparator}
{}

void DataStructures::ColouringQueue::push(DataStructures::MutableColouring* colouring)
{
    // If the colouring is already in the queue, then don't add it
    if (std::any_of(queue.begin(), queue.end(), [colouring](auto* c){return *colouring==*c;}))
        return;

    // Add the colouring to the queue
    queue.push_back(colouring);

    // Prune the queue if it has too many elements
    if (queue.size() > nbColourings)
    {
        // Find the worst element in the queue
        auto it = std::min_element(queue.begin(), queue.end(),
                                   [this](auto* c1, auto* c2){return (*evaluator)(c1, c2);});

        // Remove all the elements in the queue that have the worst evaluation
        int worstEvaluation{evaluator->evaluate(*it)};
        std::vector<DataStructures::MutableColouring*>allColourings{queue};
        queue.clear();
        std::copy_if(
            allColourings.begin(),
            allColourings.end(),
            std::back_inserter(queue),
            [this,worstEvaluation](auto* c){return evaluator->evaluate(c)>worstEvaluation;}
        );

        // If the queue is not full, then add random colourings with the worst evaluation to fill it
        if (queue.size() < nbColourings)
        {
            std::vector<DataStructures::MutableColouring*>fillUpColourings{};
            std::copy_if(
                allColourings.begin(),
                allColourings.end(),
                std::back_inserter(fillUpColourings),
                [this,worstEvaluation](auto* c){return evaluator->evaluate(c)==worstEvaluation;}
            );
            std::sample(
                fillUpColourings.begin(),
                fillUpColourings.end(),
                std::back_inserter(queue),
                nbColourings - queue.size(),
                std::mt19937{std::random_device{}()}
            );
        }

        if (queue.empty())
        {
            queue = allColourings;

//            // If all colouring have the same (worst) evaluation, then sample some randomly
//            std::sample(
//                allColourings.begin(),
//                allColourings.end(),
//                std::back_inserter(queue),
//                nbColourings,
//                std::mt19937{std::random_device{}()}
//            );
        }
    }
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
