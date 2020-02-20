#include "BackwardFlowAnalysis.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"
#include "llvm/Support/raw_ostream.h"

template<typename T>
void A::BackwardFlowAnalysis<T>::DoAnalysis(){
    llvm::errs() << "in bfa\n";
}

template<typename T>
bool A::BackwardFlowAnalysis<T>::IsForward(){
    return false;
}

template class A::BackwardFlowAnalysis<A::ArrayPackedSet<char*>>;
template class A::BackwardFlowAnalysis<A::ArraySparseSet<char*>>;
