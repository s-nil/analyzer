/**
 * @file AbstractFlowSet.cpp
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "AbstractFlowSet.h"

/**
 * @brief this is clone
 * 
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::AbstractFlowSet<T>::Clone()
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return A::FlowSet<T>* 
 */
template<typename T>
A::FlowSet<T>* A::AbstractFlowSet<T>::EmptySet()
{
  //TODO
}

 /**
  * @brief 
  * 
  * @tparam T 
  * @param dest 
  */
template<typename T>
void A::AbstractFlowSet<T>::Copy(A::FlowSet<T>* dest)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::AbstractFlowSet<T>::Clear()
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::AbstractFlowSet<T>::Union(A::FlowSet<T>* other)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @param dest 
 */
template<typename T>
void A::AbstractFlowSet<T>::Union(A::FlowSet<T>* other, A::FlowSet<T>* dest)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::AbstractFlowSet<T>::Intersection(A::FlowSet<T>* other)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @param dest 
 */
template<typename T>
void A::AbstractFlowSet<T>::Intersection(A::FlowSet<T>* other, A::FlowSet<T>* dest)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 */
template<typename T>
void A::AbstractFlowSet<T>::Difference(A::FlowSet<T>* other)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @param dest 
 */
template<typename T>
void A::AbstractFlowSet<T>::Difference(A::FlowSet<T>* other, A::FlowSet<T>* dest)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::AbstractFlowSet<T>::IsEmpty()
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return int 
 */
template<typename T>
int A::AbstractFlowSet<T>::Size()
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 */
template<typename T>
void A::AbstractFlowSet<T>::Add(T obj)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 * @param dest 
 */
template<typename T>
void A::AbstractFlowSet<T>::Add(T obj, A::FlowSet<T>* dest)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 */
template<typename T>
void A::AbstractFlowSet<T>::Remove(T obj)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 * @param dest 
 */
template<typename T>
void A::AbstractFlowSet<T>::Remove(T obj, A::FlowSet<T>* dest)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::AbstractFlowSet<T>::Contains(T obj)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::AbstractFlowSet<T>::Equals(A::FlowSet<T>* other)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @return true 
 * @return false 
 */
template<typename T>
bool A::AbstractFlowSet<T>::IsSubSet(A::FlowSet<T>* other)
{
  //TODO
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return std::list<T> 
 */
template<typename T>
std::list<T> A::AbstractFlowSet<T>::ToList()
{
  //TODO
}

template class A::AbstractFlowSet<int>;
template class A::AbstractFlowSet<char*>;
