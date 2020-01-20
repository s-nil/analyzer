#ifndef _A_ABSTRACT_FLOW_SET_H_
#define _A_ABSTRACT_FLOW_SET_H

#include "FlowSet.h"

namespace A{

template <class T>
class AbstractFlowSet : public FlowSet<T>, public IterableList<T>{
public:
    AbstractFlowSet(){}
    
    FlowSet<T>* Clone();
    FlowSet<T>* EmptySet();
    void Copy(FlowSet<T>* dest);
    void Clear();
    void Union(FlowSet<T>* other);
    void Union(FlowSet<T>* other, FlowSet<T>* dest);
    void Intersection(FlowSet<T>* other);
    void Intersection(FlowSet<T>* other, FlowSet<T>* dest);
    void Difference(FlowSet<T>* other);
    void Difference(FlowSet<T>* other, FlowSet<T>* dest);
    bool IsEmpty();
    int Size();
    void Add(T obj);
    void Add(T obj, FlowSet<T>* dest);    
    void Remove(T obj);
    void Remove(T obj, FlowSet<T>* dest);    
    bool Contains(T obj);
    bool IsSubSet(FlowSet<T>* other);
    // std::vector<T> ToList();

    void display();
};

template class A::FlowSet<int>;
}   // end namespace

#endif  // end _A_ABSTRACT_FLOW_SET_H_
