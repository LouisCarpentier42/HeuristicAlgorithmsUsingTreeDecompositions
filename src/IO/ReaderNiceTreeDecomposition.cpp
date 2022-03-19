//
// Created by louis on 11/11/2021.
//

#include "Reader.h"

std::shared_ptr<DataStructures::NiceNode> transformToNiceBag(const std::shared_ptr<DataStructures::Node>& bag)
{
    if (bag->isLeaf())
    {
        if (!bag->isEmpty()) throw std::invalid_argument("A leaf bag in a nice tree decomposition must be empty!");
        return std::make_shared<DataStructures::LeafNode>(bag->getId());
    }

    else if (bag->getNbChildren() == 1)
    {
        std::shared_ptr<DataStructures::Node> child = *bag->beginChildrenIterator();
        DataStructures::BagContent parentContent = bag->getBagContent();
        DataStructures::BagContent childContent = child->getBagContent();

        if (bag->getBagSize() + 1 == child->getBagSize()) // Forget node
        {
            DataStructures::VertexType forgottenVertex;
            bool forgottenVertexFound{false};
            for (auto itParent = parentContent.begin(), itChild = childContent.begin();
            itParent != parentContent.end();
            itParent++, itChild++)
            {
                if (*itParent != *itChild)
                {
                    forgottenVertex = *itChild;
                    forgottenVertexFound = true;
                    break;
                }
            }
            if (!forgottenVertexFound) forgottenVertex = *childContent.rbegin();

            auto niceChildForget = transformToNiceBag(child);
            return std::make_shared<DataStructures::ForgetNode>(
                bag->getId(),
                bag->getBagSize(),
                bag->getBagContent(),
                niceChildForget,
                forgottenVertex
            );
        }
        else if (bag->getBagSize() == child->getBagSize() + 1) // Introduce node
        {
            DataStructures::VertexType introducedVertex;
            bool introducedVertexFound{false};
            for (auto itParent = parentContent.begin(), itChild = childContent.begin();
                 itChild != childContent.end();
                 itParent++, itChild++)
            {
                if (*itParent != *itChild)
                {
                    introducedVertex = *itParent;
                    introducedVertexFound = true;
                    break;
                }
            }
            if (!introducedVertexFound) introducedVertex = *parentContent.rbegin();

            auto niceChildIntroduce = transformToNiceBag(child);
            return std::make_shared<DataStructures::IntroduceNode>(
                bag->getId(),
                bag->getBagSize(),
                bag->getBagContent(),
                niceChildIntroduce,
                introducedVertex
            );
        }
        else
        {
            throw std::invalid_argument("An introduce bag or forget bag must differ 1 in size compared to its child!");
        }
    }

    else if (bag->getNbChildren() == 2)
    {
        std::shared_ptr<DataStructures::Node> leftChild = *bag->beginChildrenIterator();
        std::shared_ptr<DataStructures::Node> rightChild = *(bag->beginChildrenIterator()+1);

//        // Check if the bags have the same content
//        DataStructures::BagContent parentContent = bag->getBagContent();
//        DataStructures::BagContent leftChildContent = leftChild->getBagContent();
//        DataStructures::BagContent rightChildContent = rightChild->getBagContent();
//        for (auto itParent = parentContent.begin(), itLeftChild = leftChildContent.begin(), itRightChild = rightChildContent.begin();
//             itParent != parentContent.end() && itLeftChild != leftChildContent.end() && itRightChild != rightChildContent.end();
//             itParent++, itLeftChild++, itRightChild++)
//        {
//            if (!(*itParent == *itLeftChild && *itParent == *itRightChild))
//                throw std::invalid_argument("Children of a join bag must have the same content as the parent bag!");
//        }

        auto niceLeftChildJoin = transformToNiceBag(leftChild);
        auto niceRightChildJoin = transformToNiceBag(rightChild);
        auto j = DataStructures::JoinNode{bag->getId(), bag->getBagSize(), bag->getBagContent(), niceLeftChildJoin, niceRightChildJoin};
        return std::make_shared<DataStructures::JoinNode>(
            bag->getId(),
            bag->getBagSize(),
            bag->getBagContent(),
            niceLeftChildJoin,
            niceRightChildJoin
        );
    }

    else
    {
        throw std::invalid_argument("A bag in a nice tree decomposition must have either 0, 1 or 2 children!");
    }
}

std::shared_ptr<DataStructures::NiceTreeDecomposition> IO::Reader::readNiceTreeDecomposition(const std::string &filename) const
{
    std::shared_ptr<DataStructures::TreeDecomposition> treeDecomposition = readTreeDecomposition(filename);

    return std::make_shared<DataStructures::NiceTreeDecomposition>(
        treeDecomposition->getTreeWidth(),
        transformToNiceBag(treeDecomposition->getRoot())
    );
}
