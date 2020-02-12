/**
 * @file AbstractBoundedFlowSet.cpp
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "AbstractBoundedFlowSet.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"

/**
 * @brief 
 * 
 * @tparam T 
 * @param dest 
 */
template<typename T>
void A::AbstractBoundedFlowSet<T>::Complement(A::FlowSet<T>* destFlow){
    ArrayPackedSet<T>* tmp = dynamic_cast<ArrayPackedSet<T>*>(this->Clone());
    ArraySparseSet<T>* dest = dynamic_cast<ArraySparseSet<T>*>(destFlow);
    dest->Clear();
    tmp->Complement();

    for(auto i : *tmp){
        dest->Add(i);
    }
}

// template class A::AbstractBoundedFlowSet<int>;
template class A::AbstractBoundedFlowSet<char*>;
