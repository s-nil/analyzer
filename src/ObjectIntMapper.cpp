#include "ObjectIntMapper.h"

template<typename T>
int A::ObjectIntMapper<T>::Add(T obj)
{
    objectToInt[obj] = counter;
    intToObject.push_back(obj);
    return counter++;
}

template<typename T>
int A::ObjectIntMapper<T>::GetInt(T obj)
{
    int i = objectToInt[obj];
    if(i != 0)
        return i;

    return Add(obj);
}

template<typename T>
T A::ObjectIntMapper<T>::GetObject(int idx)
{
    return intToObject[idx];    
}

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

template<typename T>
int A::ObjectIntMapper<T>::Size()
{
    return counter;
}

template class A::ObjectIntMapper<int>;