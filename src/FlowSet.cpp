#include "FlowSet.h"
#include "llvm/Support/raw_ostream.h"

template<typename T>
T A::FlowSet<T>::display()
{
    llvm::errs() << "1" << '\n';
    return 1;
}

template class A::FlowSet<int>;