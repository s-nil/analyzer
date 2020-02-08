#ifndef _A_ARRAY_PACKED_SET_H_
#define _A_ARRAY_PACKED_SET_H_
#include "AbstractBoundedFlowSet.h"
#include "ObjectIntMapper.h"
#include "llvm/ADT/BitVector.h"

namespace A
{
/**
 * @brief 
 *  Storage for a bounded lattice
 * @tparam T 
 *  Type of the object to stored
 */
template<typename T>
class ArrayPackedSet : public AbstractBoundedFlowSet<T>
{
public:
    ArrayPackedSet(){}
    ~ArrayPackedSet(){}

    ArrayPackedSet(ObjectIntMapper<T> mapper);
    ArrayPackedSet(ObjectIntMapper<T> mapper, llvm::BitVector bits);

    void Complement();  //TODO
    void Complement(FlowSet<T>* dest);  //TODO
	FlowSet<T>* TopSet();   //  TODO

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
    // void Add(T obj, FlowSet<T>* dest);      // TODO
    void Remove(T obj);
    // void Remove(T obj, FlowSet<T>* dest);    // TODO
    bool Contains(T obj);
    bool Equals(FlowSet<T>* other);
    bool IsSubSet(FlowSet<T>* other);
    std::list<T> ToList();
private:
    A::ObjectIntMapper<T> map;
    llvm::BitVector bits;

    bool SameType(A::FlowSet<T>* o);
    llvm::BitVector CopyBitSet(A::ArrayPackedSet<T>* o);
    std::list<T> ToList(llvm::BitVector bits, int base);
    std::list<T> ToList(int low, int high); //  TODO
};
}

#endif