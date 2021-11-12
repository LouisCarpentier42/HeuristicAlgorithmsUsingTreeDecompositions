//
// Created by louis on 11/11/2021.
//

#include "Reader.h"

bool containSameElements(DataStructures::BagContent& bag1, DataStructures::BagContent& bag2)
{
    if (bag1.size() != bag2.size()) return false;

    for (DataStructures::VertexType vertex : bag1)
    {
        if (std::find(bag2.begin(), bag2.end(), vertex) == bag2.end())
        {
            return false;
        }
    }
    return true;
}

DataStructures::NiceBag* transformToNiceBag(const DataStructures::Bag* bag)
{
    if (bag->isLeaf())
    {
        if (!bag->isEmpty()) throw std::invalid_argument("A leaf bag in a nice tree decomposition must be empty!");
        return new DataStructures::LeafBag{bag->getId()};
    }

    else if (bag->getNbChildren() == 1)
    {
        DataStructures::Bag* child = *bag->beginChildrenIterator();
        DataStructures::BagContent parentContent = bag->getBagContent();
        DataStructures::BagContent childContent = child->getBagContent();

        if (bag->getBagSize() + 1 == child->getBagSize()) // Forget node
        {
            std::vector<DataStructures::VertexType> forgottenVertex{};
            for (DataStructures::VertexType vertex : childContent)
            {
                if (std::find(parentContent.begin(), parentContent.end(), vertex) == parentContent.end())
                {
                    forgottenVertex.push_back(vertex);
                }
                if (forgottenVertex.size() > 1) throw std::invalid_argument("Only one vertex can be forgotten in a forget node!");
            }

            if (forgottenVertex.empty()) throw std::invalid_argument("A vertex must be forgotten in forget node!");

            return new DataStructures::ForgetVertexBag{
                bag->getId(),
                bag->getBagSize(),
                bag->getBagContent(),
                transformToNiceBag(child),
                forgottenVertex[0]
            };
        }
        else if (bag->getBagSize() == child->getBagSize() + 1) // Introduce node
        {
            std::vector<DataStructures::VertexType> introducedVertex;
            for (DataStructures::VertexType vertex : parentContent)
            {
                if (std::find(childContent.begin(), childContent.end(), vertex) == childContent.end())
                {
                    introducedVertex.push_back(vertex);
                }
                if (introducedVertex.size() > 1) throw std::invalid_argument("Only one vertex can be introduced in an introduce node!");
            }

            if (introducedVertex.empty()) throw std::invalid_argument("A vertex must be introduced in an introduce node!");

            return new DataStructures::IntroduceVertexBag{
                bag->getId(),
                bag->getBagSize(),
                bag->getBagContent(),
                transformToNiceBag(child),
                introducedVertex[0]
            };
        }
        else
        {
            throw std::invalid_argument("An introduce bag or forget bag must differ 1 in size compared to its child!");
        }
    }

    else if (bag->getNbChildren() == 2)
    {
        DataStructures::Bag* leftChild = *bag->beginChildrenIterator();
        DataStructures::Bag* rightChild = *(bag->beginChildrenIterator()+1);

        DataStructures::BagContent parentContent = bag->getBagContent();
        DataStructures::BagContent leftChildContent = leftChild->getBagContent();
        DataStructures::BagContent rightChildContent = rightChild->getBagContent();

        if (!containSameElements(parentContent, leftChildContent) ||
            !containSameElements(parentContent, rightChildContent))
        {
            std::cout << "ID: " << bag->getId() << '\n';
            throw std::invalid_argument("Children of a join bag must have the same content as the parent bag!");
        }

        return new DataStructures::JoinBag{
            bag->getId(),
            bag->getBagSize(),
            bag->getBagContent(),
            transformToNiceBag(leftChild),
            transformToNiceBag(rightChild)
        };
    }

    else
    {
        throw std::invalid_argument("A bag in a nice tree decomposition must have either 0, 1 or 2 children!");
    }
}

DataStructures::NiceTreeDecomposition IO::Reader::readNiceTreeDecomposition(std::string &filename) const
{
    DataStructures::TreeDecomposition treeDecomposition = readTreeDecomposition(filename);

    return DataStructures::NiceTreeDecomposition{
        treeDecomposition.getTreeWidth(),
        transformToNiceBag(treeDecomposition.getRoot())
    };
}
