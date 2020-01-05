#ifndef _A_FLOWSET_H_
#define _A_FLOWSET_H_

#include <iostream>
#include "llvm/IR/Value.h"

using namespace std;

namespace A{

template<class T>
class FlowSet
{
    class Node;

public:
    FlowSet() noexcept
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

        friend class FlowSet;
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
typename FlowSet<T>::Node* FlowSet<T>::pRootNode = nullptr;

}   //  


#endif  // 
