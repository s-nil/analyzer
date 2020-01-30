/**
 * @file AbstractFlowSet.h
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _A_ABSTRACT_FLOW_SET_H_
#define _A_ABSTRACT_FLOW_SET_H_

#include "FlowSet.h"

namespace A{

/**
 * @brief 
 * 
 * @tparam T 
 */
template <class T>
class AbstractFlowSet : public FlowSet<T>{
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
    bool Equals(FlowSet<T>* other);
    bool IsSubSet(FlowSet<T>* other);
    std::list<T> ToList();
};

// template class A::FlowSet<int>;
}   // end namespace

#endif  // end _A_ABSTRACT_FLOW_SET_H_
