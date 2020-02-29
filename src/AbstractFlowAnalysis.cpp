#include "AbstractFlowAnalysis.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"

template<typename T>
void A::AbstractFlowAnalysis<T>::SetFunction(llvm::Function* f){
    func = f;
    graph = new A::FunctionCFG(f);
}

template class A::AbstractFlowAnalysis<A::ArrayPackedSet<A::Variable>>;
template class A::AbstractFlowAnalysis<A::ArraySparseSet<A::Variable>>;