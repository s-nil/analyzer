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
            elements = std::vector<T>(0);
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
        bool IsSubSet(FlowSet<T>* other);        //  TODO
        std::list<T> ToList();

        class Iterator{
        public:
            typedef Iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::input_iterator_tag iterator_category;
            Iterator(){_ptr = nullptr;}
            Iterator(ArraySparseSet<T>* b){
                if(!b->elements.empty()){
                    setObject = b;
                    _ptr = &b->elements[0];
                    idx =  0;
                }else{
                    _ptr = nullptr;
		}
	    }
            Iterator(const Iterator& cit){
                _ptr = cit._ptr;
                idx = cit.idx;
                setObject = cit.setObject;
            }
            Iterator& operator++(){
                if(idx == setObject->elements.size()-1){
                    _ptr = nullptr;
                }else{
                    ++_ptr;
                    ++idx;
                }
                return *this;
            }
            Iterator operator++(int){
                self_type tmp(*this);
                operator++();
                return tmp;
            }
            bool operator==(const Iterator& rhs) const{
                return _ptr == rhs._ptr;
            }
            bool operator!=(const Iterator& rhs) const{
                return _ptr != rhs._ptr;
            }
            value_type operator*(){
                return *_ptr;
            }
        private:
            pointer _ptr;
            ArraySparseSet<T>* setObject;
            int idx;
        };

        Iterator begin(){
            return Iterator(this);
        }
        Iterator end(){
            return Iterator();
        }


    private:
        std::vector<T> elements;
        ArraySparseSet(const ArraySparseSet<T>* ref);
        bool SameType(A::FlowSet<T>* o);
    };    

// template<typename T>
// struct is_pointer{static const bool v = false;};

// template<typename T>
// struct is_pointer<T*>{static const bool v = true;};
}

#endif
