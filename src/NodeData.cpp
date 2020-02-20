#include "NodeData.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"

template<typename T>
std::string A::NodeData<T>::GetNodeName(){
    return node->getName().str();
}

template<typename T>
T A::NodeData<T>::GetInFlow(){
    return inFlow;
}

template<typename T>
T A::NodeData<T>::GetOutFlow(){
    return outFlow;
}

template class A::NodeData<A::ArrayPackedSet<char*>>;
template class A::NodeData<A::ArraySparseSet<char*>>;