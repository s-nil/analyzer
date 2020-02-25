#include "NodeData.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"

/**
 * @brief 
 * 
 * @tparam T 
 * @return std::string 
 */
template<typename T>
inline std::string A::NodeData<T>::GetNodeName(){
    if(node)
        return node->getName().str();
    return "";
}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
inline void A::NodeData<T>::AddIn(A::NodeData<T>* n){
    incoming.push_back(n);
}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::NodeData<T>::AddIn(llvm::SmallVector<A::NodeData<T>*,0> list){
    for(auto I=list.begin(),E=list.end(); I!=E; ++I){
        AddIn(*I);
    }
}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
inline void A::NodeData<T>::AddOut(A::NodeData<T>* n){
    outgoing.push_back(n);
}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::NodeData<T>::AddOut(llvm::SmallVector<A::NodeData<T>*,0> list){
    for(auto I=list.begin(),E=list.end(); I!=E; ++I){
        AddOut(*I);
    }
}

/**
 * @brief 
 * 
 * @return llvm::SmallVector<llvm::BasicBlock*,0> 
 */
template<typename T>
llvm::SmallVector<llvm::BasicBlock*,0> A::NodeData<T>::GetINcoming(){
    llvm::SmallVector<llvm::BasicBlock*,0> tmp;
    for(auto I = incoming.begin(), IE = incoming.end(); I!=IE; ++I ){
        tmp.push_back((*I)->node);
    }
    return tmp;
}

/**
 * @brief Get the Outgoing object
 * 
 * @return llvm::SmallVector<llvm::BasicBlock*,0> 
 */
template<typename T>
llvm::SmallVector<llvm::BasicBlock*,0> A::NodeData<T>::GetOutgoing(){
llvm::SmallVector<llvm::BasicBlock*,0> tmp;
    for(auto I = outgoing.begin(), IE = outgoing.end(); I!=IE; ++I ){
        tmp.push_back((*I)->node);
    }
    return tmp;
}

template class A::NodeData<A::ArrayPackedSet<char*>>;
template class A::NodeData<A::ArraySparseSet<char*>>;