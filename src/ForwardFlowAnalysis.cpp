#include "ForwardFlowAnalysis.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"
#include "llvm/Support/raw_ostream.h"

template<typename T>
void A::ForwardFlowAnalysis<T>::DoAnalysis(){
    llvm::errs() << "in ffa\n";
    this->Compute();
}

template<typename T>
bool A::ForwardFlowAnalysis<T>::IsForward(){
    return true;
}

template class A::ForwardFlowAnalysis<A::ArrayPackedSet<char*>>;
template class A::ForwardFlowAnalysis<A::ArraySparseSet<char*>>;
