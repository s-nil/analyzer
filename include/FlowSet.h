#ifndef _A_FLOW_SET_H_
#define _A_FLOW_SET_H_

#include "IterableList.h"
#include <vector>

namespace A{

template<typename T>
class FlowSet
{
public:
    // FlowSet(){}

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
    virtual bool IsSubSet(FlowSet<T>* other) = 0;
    // std::vector<T> ToList();
    virtual void display() = 0;
    virtual ~FlowSet(){};
private:

};

}   // end namespace

#endif  //  end _A_FLOW_SET_H_