/**
 * @file IterableList.cpp
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "IterableList.h"

/**
 * @brief 
 * 
 * @tparam T 
 * @param data 
 */
template <typename T>
void A::IterableList<T>::push_back(T data)
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

template class A::IterableList<llvm::Value*>;
template class A::IterableList<int>;
