//
// Created by louis on 10/11/2021.
//

#ifndef HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEFORGETVERTEXBAGBASE_H
#define HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEFORGETVERTEXBAGBASE_H

#include "NiceBag.h"

namespace DataStructures
{
    class IntroduceForgetVertexBagBase : public NiceBag
    {
    protected:
        const DataStructures::VertexType specialVertex;
    private:
        const NiceBag* child{nullptr};

    protected:
        IntroduceForgetVertexBagBase(int id, size_t size, BagContent vertices, NiceBag* child, BagType , VertexType specialVertex);

    public:
        [[nodiscard]] const NiceBag* getChild() const;
    };
}

#endif //HEURISTICALGORITHMSUSINGTREEDECOMPOSITIONS_INTRODUCEFORGETVERTEXBAGBASE_H
