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
    objectToInt[obj] = counter;
    intToObject.push_back(obj);
    return counter++;
}

/**
 * @brief 
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
        return i;

    return Add(obj);
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param idx 
 * @return T 
 */
template<typename T>
T A::ObjectIntMapper<T>::GetObject(int idx)
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
bool A::ObjectIntMapper<T>::Contains(T obj)
{
    for(auto it = objectToInt.begin(); it!=objectToInt.end(); ++it)
    {
        llvm::errs() << it->first << '\n';
    }

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
int A::ObjectIntMapper<T>::Size()
{
    return counter;
}

template class A::ObjectIntMapper<int>;