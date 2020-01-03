#include "FlowSet.h"

template <typename T>
typename A::FlowSet<T>::Node* A::FlowSet<T>::pRootNode = nullptr;

template <typename T>
void A::FlowSet<T>::push_back(T data)
{
    Node* pTemp = getNode(data);
    if(!getRoot())
    {
        this->getRoot() = pTemp;
    }
    else
    {
        Node* nTmp = getRoot();
        while (nTmp->next)
        {
            nTmp = nTmp->next;
        }
        nTmp->next = pTemp;        
    }   
}