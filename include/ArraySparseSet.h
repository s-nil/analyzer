#ifndef _A_ARRAY_SPARSE_SET_H_
#define _A_ARRAY_SPARSE_SET_H_
#include "AbstractFlowSet.h"
#include <vector>
#include <list>

namespace A{
    template<typename T>
    class ArraySparseSet : public AbstractFlowSet<T>{
    public:
        ArraySparseSet(){
            elements = vector<T>(0);
        }
        ~ArraySparseSet(){}

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
        void Remove(int idx);
        // void Remove(T obj, FlowSet<T>* dest);    // TODO
        bool Contains(T obj);
        bool Equals(FlowSet<T>* other);
        // bool IsSubSet(FlowSet<T>* other);
        std::list<T> ToList();
    private:
        std::vector<T> elements;
        ArraySparseSet(const ArraySparseSet<T>* ref);
        bool SameType(A::FlowSet<T>* o);
    };    

template<typename T>
struct is_pointer{static const bool v = false;};

template<typename T>
struct is_pointer<T*>{static const bool v = true;};
}

#endif