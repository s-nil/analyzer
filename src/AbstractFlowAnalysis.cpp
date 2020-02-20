#include "AbstractFlowAnalysis.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"

template<typename T>
void A::AbstractFlowAnalysis<T>::SetFunction(llvm::Function* f){
    func = f;
}

template class A::AbstractFlowAnalysis<A::ArrayPackedSet<char*>>;
template class A::AbstractFlowAnalysis<A::ArraySparseSet<char*>>;
template class A::AbstractFlowAnalysis<int>;
template class A::AbstractFlowAnalysis<char*>;