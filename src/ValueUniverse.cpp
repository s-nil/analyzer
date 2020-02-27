#include "ValueUniverse.h"

template<>
A::ValueUniverse<A::Variable*>::ValueUniverse(llvm::Function* f){
    llvm::errs() << "Same\n";
    ele = std::vector<A::Variable*>();
    for (auto I = f->arg_begin(); I != f->arg_end(); ++I){
        A::Variable* var = new A::Variable(I);
        ele.push_back(var);
    }
    for (llvm::inst_iterator I = llvm::inst_begin(*f); I != llvm::inst_end(*f); ++I){
        llvm::Value* v = &*I;
        if((*I).hasName()){
            A::Variable* var = new A::Variable(v);
            ele.push_back(var);
        }
    }
}

template<>
A::ValueUniverse<char*>::ValueUniverse(llvm::Function* f){
    llvm::errs() << "Not Same\n";
}

/**
 * @brief Construct a new A:: Value Universe< T>:: Array Value Universe object
 * 
 * @tparam T 
 * @param e 
 */
template<typename T>
A::ValueUniverse<T>::ValueUniverse(std::vector<T> e){
    this->ele = e;
}

/**
 * @brief 
 *  Returns size of the domain
 * @tparam T 
 * @return int 
 */
template<typename T>
inline int A::ValueUniverse<T>::Size(){
    return ele.size();
}

/**
 * @brief 
 *  Returns elements in the domain in a vector
 * @tparam T 
 * @return std::vector<T> 
 */
template<typename T>
inline std::vector<T> A::ValueUniverse<T>::ToArray(){
    return ele;
}

/**
 * @brief 
 *  begin function for the iterator
 * @tparam T 
 * @return A::ValueUniverse<T>::Iterator 
 */
template<class T>
inline auto A::ValueUniverse<T>::begin() -> A::ValueUniverse<T>::Iterator{
    return A::ValueUniverse<T>::Iterator(this);
}

/**
 * @brief 
 *  end function for the iterator
 * @tparam T 
 * @return A::ValueUniverse<T>::Iterator 
 */
template<class T>
inline auto A::ValueUniverse<T>::end() -> A::ValueUniverse<T>::Iterator{
    return A::ValueUniverse<T>::Iterator();
}

template class A::ValueUniverse<char*>;
template class A::ValueUniverse<A::Variable*>;