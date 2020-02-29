/**
 * @file ObjectIntMapper.cpp
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "ObjectIntMapper.h"

/**
 * @brief 
 * 
 * @tparam T 
 * @param obj 
 * @return int 
 */
template<typename T>
int A::ObjectIntMapper<T>::Add(T obj)
{
    objectToInt[obj] = ++counter;
    intToObject.push_back(obj);
    return counter;
}

/**
 * @brief 
 * Return the index of the object
 * 
 * @tparam T 
 * @param obj 
 * @return int 
 */
template<typename T>
int A::ObjectIntMapper<T>::GetInt(T obj)
{
    int i = objectToInt[obj];
    if(i != 0)
        return i-1;

    return Add(obj)-1;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param idx 
 * @return T 
 */
template<typename T>
inline T A::ObjectIntMapper<T>::GetObject(int idx)
{
    return intToObject[idx];    
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
inline bool A::ObjectIntMapper<T>::Contains(T obj)
{
    if(objectToInt.find(obj) != objectToInt.end())
        return 1;
    return 0;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return int 
 */
template<typename T>
inline int A::ObjectIntMapper<T>::Size()
{
    return counter;
}

template<typename T>
inline bool A::ObjectIntMapper<T>::operator==(A::ObjectIntMapper<T> rhs)
{
    return intToObject == rhs.intToObject && counter == rhs.counter && objectToInt == rhs.objectToInt;
}

template<typename T>
inline bool A::ObjectIntMapper<T>::operator!=(A::ObjectIntMapper<T> rhs)
{
    return !operator==(rhs);
}

template class A::ObjectIntMapper<A::Variable>;