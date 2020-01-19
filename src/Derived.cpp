#include "Derived.h"

template<typename T>
void L::Derived<T>::set(const T& val)
{
    Base<T>::set(val);
}

template<typename T>
T& L::Derived<T>::get()
{
    return Base<T>::get(); 
}

template class L::Derived<int>;