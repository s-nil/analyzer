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

    void Complement();
    void Complement(FlowSet<T>* dest);
	FlowSet<T>* TopSet();

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

    class Iterator{
    public:
	typedef Iterator self_type;
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::input_iterator_tag iterator_category;
	Iterator(){
	    idx = -1;
	}
	Iterator(ArrayPackedSet<T>* obj){
	    if(obj->IsEmpty()){
		idx = -1;
	    }else{
	        setObject = obj;
		idx = obj->bits.find_first();
	    }
	}
	Iterator(const Iterator& cit){
	    setObject = cit.setObject;
	    idx = cit.idx;
	}
	Iterator& operator++(){
	    if(idx == setObject->bits.find_last()){
		idx = -1;
	    }else{
		idx = setObject->bits.find_next(idx);
	    }
	    return *this;
	}
	Iterator operator++(int){
	    self_type tmp(*this);
	    operator++();
	    return tmp;
	}
	bool operator==(const Iterator& rhs){
	   return idx == rhs.idx;
	}
	bool operator!=(const Iterator& rhs){
	    return idx != rhs.idx;
	}
	value_type operator*(){
	    return setObject->map.GetObject(idx);
	}
    private:
	ArrayPackedSet<T>* setObject;
	int idx;
    };
    Iterator begin(){
	return Iterator(this);
    }
    Iterator end(){
	return Iterator();
    }
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
