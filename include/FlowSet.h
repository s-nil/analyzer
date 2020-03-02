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

#include <list>

namespace A{

/**
 * @brief 
 *  An abstract class, basically an interface providing function declarations for the derived classes.
 *  Represents data for an DF analysis. These functions are used by a latice implementation.
 *  The elements are expressed by the ValueUniverse.
 * @tparam T 
 *  Type of the dataflow value
 */
template<typename T>
class FlowSet{
public:
    /// returns a clone object same as current object(this)
    virtual FlowSet<T>* Clone() = 0;
    //  returns an emptyset
    virtual FlowSet<T>* EmptySet() = 0;
    /// copy current object(this) in the dest
    virtual void Copy(FlowSet<T>* dest) = 0;
    /// clears the current object
    virtual void Clear() = 0;
    /// unions current and other, puts result in the current
    virtual void Union(FlowSet<T>* other) = 0;
    /// unions current and other, puts result in the dest
    virtual void Union(FlowSet<T>* other, FlowSet<T>* dest) = 0;
    /// intersection of current and other, puts result in the current
    virtual void Intersection(FlowSet<T>* other) = 0;
    /// intersection of the current and other, puts result in the dest
    virtual void Intersection(FlowSet<T>* other, FlowSet<T>* dest) = 0;
    /// difference of current and other, puts result in the current
    virtual void Difference(FlowSet<T>* other) = 0;
    /// difference of the current and other, puts result in the dest
    virtual void Difference(FlowSet<T>* other, FlowSet<T>* dest) = 0;
    /// returns true if current object is empty
    virtual bool IsEmpty() = 0;
    /// returns size of the current object
    virtual int Size() = 0;
    /// adds obj in the current object
    virtual void Add(T obj) = 0;
    /// puts the union the obj and this in the dest
    virtual void Add(T obj, FlowSet<T>* dest) = 0;
    /// removes obj from the current object
    virtual void Remove(T obj) = 0;
    /// puts the this minus obj in the dest
    virtual void Remove(T obj, FlowSet<T>* dest) = 0;    
    /// returns true if obj is present in current object
    virtual bool Contains(T obj) = 0;
    /// compares current object with other, returns 0 if both are same
    virtual bool Equals(FlowSet<T>* other) = 0;
    /// returns true if other is a subset of current object
    virtual bool IsSubSet(FlowSet<T>* other) = 0;
    /// returns a list of DF values that current object contains
    virtual std::list<T> ToList() = 0;
    virtual ~FlowSet(){}
private:

};

}   // end namespace

#endif  //  end _A_FLOW_SET_H_