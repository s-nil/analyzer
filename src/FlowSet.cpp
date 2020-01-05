#include "FlowSet.h"

template <typename T>
void A::FlowSet<T>::push_back(T data)
{
    Node* pTemp = getNode(data);
    if(!getRootNode())	
    {
        getRootNode() = pTemp;
    }
    else
    {
        Node* nTmp = getRootNode();
        while (nTmp->next)
        {
            nTmp = nTmp->next;
        }
        nTmp->next = pTemp;        
    }   
}

template class A::FlowSet<llvm::Value*>;
