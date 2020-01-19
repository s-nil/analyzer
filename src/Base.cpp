#include "Base.h"

template<typename T>
void L::Base<T>::set(const T& val)
{
    data = val;
}

template<typename T>
T& L::Base<T>::get()
{
    return data;
}

template<typename T>
void L::Base<T>::print(){}

template class L::Base<int>;