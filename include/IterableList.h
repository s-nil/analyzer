#ifndef _A_ITERABLE_LIST_H_
#define _A_ITERABLE_LIST_H_

#include <iostream>
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"

using namespace std;

namespace A{

template<typename T>
class IterableList
{
    class Node;

public:
    IterableList() noexcept
    {
        pRootNode = nullptr;
    }

    class Iterator;

    Iterator begin()
    {
        return Iterator(pRootNode);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    void push_back(T data);

    class Iterator
    {
    public:
        Iterator() noexcept:
	    currentNode(pRootNode){ }

        Iterator(const Node* pNode) noexcept: 
	    currentNode(pNode){	}

        Iterator& operator=(Node* node)
        {
            this->currentNode = node;
            return *this;
        }

        // prefix
        Iterator& operator++()
        {
            if(currentNode)
                currentNode = currentNode->next;
            return *this;
        }

        // postfix : must be non reference
        Iterator operator++(int)
        {
            Iterator it = *this;
            ++(*this);
            return it;
        }

        bool operator!=(const Iterator& it)
        {
            return this->currentNode != it.currentNode;
        }

	bool operator==(const Iterator& it)
	{
	    return this->currentNode == it.currentNode;
	}

        T operator*()
        {
            return currentNode->data;
        }


    private:
        const Node* currentNode;
    };
    
private:
    class Node
    {
        T data;
        Node* next;

        friend class IterableList;
    };

    Node* getNode(T d)
    {
        Node *newNode = new Node;
        newNode->data = d;
        newNode->next = nullptr;

        return newNode;
    }

    Node*& getRootNode()
    {
        return pRootNode;
    }
    
    static Node* pRootNode;

};

template <typename T>
typename IterableList<T>::Node* IterableList<T>::pRootNode = nullptr;

}   //  

#endif  // 
