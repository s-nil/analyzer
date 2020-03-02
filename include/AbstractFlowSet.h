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
#include "llvm/Support/raw_ostream.h"

namespace A{

/**
 * @brief 
 * 
 * @tparam T 
 */
template <class T>
class AbstractFlowSet : public FlowSet<T>{
public:
    /// Used when called by a FlowSet pointer
    FlowSet<T>* Clone();
    /// Used when called by a FlowSet pointer
    FlowSet<T>* EmptySet();
    /// copy current object in dest, type of this and dest are different
    void Copy(FlowSet<T>* dest);
    /// Used when called by a FlowSet pointer
    void Clear();
    /// unions current and other, puts result in the current, type of this and other are different
    void Union(FlowSet<T>* other);
    /// unions current and other, puts result in the dest, types are different
    void Union(FlowSet<T>* other, FlowSet<T>* dest);
    /// intersection of current and other, puts result in the current, type of this and other are different
    void Intersection(FlowSet<T>* other);
    /// intersection of current and other, puts result in the dest, types are different
    void Intersection(FlowSet<T>* other, FlowSet<T>* dest);
    /// difference of current and other, puts result in the current, type of this and other are different
    void Difference(FlowSet<T>* other);
    /// difference of current and other, puts result in the dest, types are different
    void Difference(FlowSet<T>* other, FlowSet<T>* dest);
    /// Used when called by a FlowSet pointer
    bool IsEmpty();
    /// Used when called by a FlowSet pointer
    int Size();
    /// Used when called by a FlowSet pointer
    void Add(T obj);
    /// Handles both 1. when this and dest type's are same 2. types are different
    void Add(T obj, FlowSet<T>* dest);    
    /// Used when called by a FlowSet pointer
    void Remove(T obj);
    /// Handles both 1. when this and dest type's are same 2. types are different
    void Remove(T obj, FlowSet<T>* dest);    
    /// Used when called by a FlowSet pointer
    bool Contains(T obj);
    /// compares current object with other, returns 0 if both are same, type of this and other are different
    bool Equals(FlowSet<T>* other);
    /// returns true if other is a subset of current object, type of this and other are different
    bool IsSubSet(FlowSet<T>* other);
};

}   // end namespace

#endif  // end _A_ABSTRACT_FLOW_SET_H_
