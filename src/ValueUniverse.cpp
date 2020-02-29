#include "ValueUniverse.h"
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */

template<>
A::ValueUniverse<A::Variable>::ValueUniverse(llvm::Function* f){
    bool noCallSite = 1;
    ele = std::vector<A::Variable>();
    for (auto I = f->arg_begin(); I != f->arg_end(); ++I){
        // llvm::errs() << I->getName()<< '\n';
        A::Variable var = A::Variable(I);
        ele.push_back(var);
    }
    for (llvm::inst_iterator I = llvm::inst_begin(*f); I != llvm::inst_end(*f); ++I){
        llvm::CallSite cs(&*I);
        if(cs.getInstruction() && !(*I).isLifetimeStartOrEnd()){
            noCallSite = 0;
            llvm::errs() << *I << '\n';
            break;
        }
        if((*I).isLifetimeStartOrEnd()){
            continue;
        }
        if((*I).hasName()){
            llvm::Value* v = &*I;
            // llvm::errs() << (*I).getName()<<'\n';
            A::Variable var = A::Variable(v);
            ele.push_back(var);
        }
    }
    if(!(noCallSite == 1)){
        llvm::errs() << RED <<"Assertion : a function call is found.\n" << RESET <<'\n';
        exit(1);        
    }
}

template<>
A::ValueUniverse<char*>::ValueUniverse(llvm::Function* f){

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

template class A::ValueUniverse<A::Variable>;