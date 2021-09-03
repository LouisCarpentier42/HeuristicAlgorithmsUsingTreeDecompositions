//
// Created by louis on 03/09/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H

#include <iostream>
#include <vector>

namespace TreeDecomposition {

    class Bag
    {
    private:
        const int id;
        size_t size;
        std::vector<int> vertices;
        std::vector<Bag*> children;

    public:
        Bag(int id, std::vector<int> vertices);

        void addChild(Bag* child);

        friend std::ostream& operator<<(std::ostream& out, const Bag& bag);
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_BAG_H
