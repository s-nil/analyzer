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

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::AbstractBoundedFlowSet<T>::Complement()
{

}

/**
 * @brief 
 * 
 * @tparam T 
 * @param dest 
 */
template<typename T>
void A::AbstractBoundedFlowSet<T>::Complement(A::FlowSet<T>* dest)
{

}

/**
 * @brief 
 * 
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::AbstractBoundedFlowSet<T>::TopSet()
{

}

// template class A::AbstractBoundedFlowSet<int>;
template class A::AbstractBoundedFlowSet<char*>;
