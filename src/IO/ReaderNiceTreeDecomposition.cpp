//
// Created by louis on 11/11/2021.
//

#include "Reader.h"

bool containSameElements(DataStructures::BagContent& bag1, DataStructures::BagContent& bag2)
{
    if (bag1.size() != bag2.size()) return false;
    return std::all_of(
            bag1.begin(),
            bag1.end(),
            [bag2](DataStructures::VertexType vertex){ return std::find(bag2.begin(), bag2.end(), vertex) != bag2.end(); }
        );
}

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

            auto niceChildForget = transformToNiceBag(child);
            return std::make_shared<DataStructures::ForgetNode>(
                bag->getId(),
                bag->getBagSize(),
                bag->getBagContent(),
                niceChildForget,
                forgottenVertex[0]
            );
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

            auto niceChildIntroduce = transformToNiceBag(child);
            return std::make_shared<DataStructures::IntroduceNode>(
                bag->getId(),
                bag->getBagSize(),
                bag->getBagContent(),
                niceChildIntroduce,
                introducedVertex[0]
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

        DataStructures::BagContent parentContent = bag->getBagContent();
        DataStructures::BagContent leftChildContent = leftChild->getBagContent();
        DataStructures::BagContent rightChildContent = rightChild->getBagContent();

        if (!containSameElements(parentContent, leftChildContent) ||
            !containSameElements(parentContent, rightChildContent))
        {
            std::cout << "ID parent: " << bag->getId() << '\n';
            std::cout << "Content parent: ";
            for (auto x : parentContent)
                std::cout << x << " ";
            std::cout << "\n";

            std::cout << "ID left: " << leftChild->getId() << '\n';
            std::cout << "Content left: ";
            for (auto x : leftChildContent)
                std::cout << x << " ";
            std::cout << "\n";

            std::cout << "ID right: " << rightChild->getId() << '\n';
            std::cout << "Content right: ";
            for (auto x : rightChildContent)
                std::cout << x << " ";
            std::cout << "\n";



            throw std::invalid_argument("Children of a join bag must have the same content as the parent bag!");
        }

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
