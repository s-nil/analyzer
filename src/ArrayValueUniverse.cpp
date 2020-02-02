#include "ArrayValueUniverse.h"

/**
 * @brief Construct a new A:: Array Value Universe< T>:: Array Value Universe object
 * 
 * @tparam T 
 * @param e 
 */
template<typename T>
A::ArrayValueUniverse<T>::ArrayValueUniverse(std::vector<T> e){
    this->ele = e;
}

/**
 * @brief 
 *  Returns size of the domain
 * @tparam T 
 * @return int 
 */
template<typename T>
int A::ArrayValueUniverse<T>::Size(){
    return ele.size();
}

/**
 * @brief 
 *  Returns elements in the domain in a vector
 * @tparam T 
 * @return std::vector<T> 
 */
template<typename T>
std::vector<T> A::ArrayValueUniverse<T>::ToArray(){
    return ele;
}

/**
 * @brief 
 *  begin function for the iterator
 * @tparam T 
 * @return A::ArrayValueUniverse<T>::Iterator 
 */
template<class T>
auto A::ArrayValueUniverse<T>::begin() -> A::ArrayValueUniverse<T>::Iterator{
    return A::ArrayValueUniverse<T>::Iterator(this);
}

/**
 * @brief 
 *  end function for the iterator
 * @tparam T 
 * @return A::ArrayValueUniverse<T>::Iterator 
 */
template<class T>
auto A::ArrayValueUniverse<T>::end() -> A::ArrayValueUniverse<T>::Iterator{
    return A::ArrayValueUniverse<T>::Iterator();
}

template class A::ArrayValueUniverse<int>;
