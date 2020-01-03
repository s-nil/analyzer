#ifndef _A_FLOWSET_H_
#define _A_FLOWSET_H_

#include <iostream>

using namespace std;

namespace A{

template<typename T>
class FlowSet
{
    class Node;

public:
    FlowSet<T>()
    {
        pRootNode = nullptr;
    }

    class Iterator;

    Iterator begin()
    {
        return Iterator(this->pRootNode);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    void push_back(T data);

    class Iterator
    {
    public:
        Iterator(): currentNode(pRootNode){}

        Iterator(const Node* pNode): currentNode(pNode){}

        Iterator& operator=(Node* node)
        {
            this->currentNode = node;
            return &this;
        }

        // prefix
        Iterator& operator++()
        {
            if(currentNode)
                currentNode = currentNode->next;
            return &this;
        }

        // prefix
        Iterator& operator++(int)
        {
            Iterator it = *this;
            ++*this;
            return it;
        }

        Iterator& operator!=(const Iterator& it)
        {
            return this->currentNode != it.currentNode;
        }

        int operator*()
        {
            return currentNode->data;
        }


    private:
        Node* currentNode;
    };
    
private:
    class Node
    {
    public:
        T data;
        Node* next;

        friend class FlowSet;
    };

    Node* getNode(T d)
    {
        Node *n = new Node;
        n->data = d;
        n->next = nullptr;
        return n;
    }

    Node* getRoot()
    {
        return pRootNode;
    }
    
    static Node* pRootNode;

};

}   //  


#endif  // 