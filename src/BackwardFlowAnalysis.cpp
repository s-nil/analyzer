#include "BackwardFlowAnalysis.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"
#include "llvm/Support/raw_ostream.h"

template<typename T>
void A::BackwardFlowAnalysis<T>::DoAnalysis(){
    this->Compute();
}

template<typename T>
inline bool A::BackwardFlowAnalysis<T>::IsForward(){
    return false;
}

template class A::BackwardFlowAnalysis<A::ArrayPackedSet<A::Variable>>;
template class A::BackwardFlowAnalysis<A::ArraySparseSet<A::Variable>>;
