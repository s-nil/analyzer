/**
 * @file FlowSet.h
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _A_FLOW_SET_H_
#define _A_FLOW_SET_H_

#include "Iterable.h"
#include <list>

namespace A{

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
class FlowSet
{
public:
    virtual FlowSet<T>* Clone() = 0;
    virtual FlowSet<T>* EmptySet() = 0;
    virtual void Copy(FlowSet<T>* dest) = 0;
    virtual void Clear() = 0;
    virtual void Union(FlowSet<T>* other) = 0;
    virtual void Union(FlowSet<T>* other, FlowSet<T>* dest) = 0;
    virtual void Intersection(FlowSet<T>* other) = 0;
    virtual void Intersection(FlowSet<T>* other, FlowSet<T>* dest) = 0;
    virtual void Difference(FlowSet<T>* other) = 0;
    virtual void Difference(FlowSet<T>* other, FlowSet<T>* dest) = 0;
    virtual bool IsEmpty() = 0;
    virtual int Size() = 0;
    virtual void Add(T obj) = 0;
    virtual void Add(T obj, FlowSet<T>* dest) = 0;
    virtual void Remove(T obj) = 0;
    virtual void Remove(T obj, FlowSet<T>* dest) = 0;    
    virtual bool Contains(T obj) = 0;
    virtual bool Equals(FlowSet<T>* other) = 0;
    virtual bool IsSubSet(FlowSet<T>* other) = 0;
    virtual std::list<T> ToList() = 0;
    virtual ~FlowSet(){}
private:

};

}   // end namespace

#endif  //  end _A_FLOW_SET_H_