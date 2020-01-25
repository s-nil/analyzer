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

}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::AbstractFlowSet<T>::Clear()
{

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

}
    
/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::AbstractFlowSet<T>::Display()
{

}

template class A::AbstractFlowSet<int>;
