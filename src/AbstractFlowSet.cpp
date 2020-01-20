#include "AbstractFlowSet.h"


template<typename T>
A::FlowSet<T>* A::AbstractFlowSet<T>::Clone()
{

}

template<typename T>
A::FlowSet<T>* A::AbstractFlowSet<T>::EmptySet()
{

}

template<typename T>
void A::AbstractFlowSet<T>::Copy(A::FlowSet<T>* dest)
{

}

template<typename T>
void A::AbstractFlowSet<T>::Clear()
{

}

template<typename T>
void A::AbstractFlowSet<T>::Union(A::FlowSet<T>* other)
{

}

template<typename T>
void A::AbstractFlowSet<T>::Union(A::FlowSet<T>* other, A::FlowSet<T>* dest)
{

}

template<typename T>
void A::AbstractFlowSet<T>::Intersection(A::FlowSet<T>* other)
{

}

template<typename T>
void A::AbstractFlowSet<T>::Intersection(A::FlowSet<T>* other, A::FlowSet<T>* dest)
{

}

template<typename T>
void A::AbstractFlowSet<T>::Difference(A::FlowSet<T>* other)
{

}

template<typename T>
void A::AbstractFlowSet<T>::Difference(A::FlowSet<T>* other, A::FlowSet<T>* dest)
{

}

template<typename T>
bool A::AbstractFlowSet<T>::IsEmpty()
{

}

template<typename T>
int A::AbstractFlowSet<T>::Size()
{

}

template<typename T>
void A::AbstractFlowSet<T>::Add(T obj)
{

}

template<typename T>
void A::AbstractFlowSet<T>::Add(T obj, A::FlowSet<T>* dest)
{

}

template<typename T>
void A::AbstractFlowSet<T>::Remove(T obj)
{

}

template<typename T>
void A::AbstractFlowSet<T>::Remove(T obj, A::FlowSet<T>* dest)
{

}

template<typename T>
bool A::AbstractFlowSet<T>::Contains(T obj)
{

}

template<typename T>
bool A::AbstractFlowSet<T>::IsSubSet(A::FlowSet<T>* other)
{
    
}

template<typename T>
void A::AbstractFlowSet<T>::display()
{
    for (auto i = this->begin(); i != this->end() ; ++i)
    {
        llvm::errs() << *i <<' '; 
    }
    llvm::errs() <<'\n';
}

template class A::AbstractFlowSet<int>;