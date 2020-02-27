#ifndef _A_VALUSE_UNIVERSE_H_
#define _A_VALUSE_UNIVERSE_H_
#include <iterator>
#include <vector>
#include <type_traits>
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Support/raw_ostream.h"
#include "Variable.h"

namespace A{
    /**
     * @brief 
     *  An implementation of the domain that'll be used in bounded set
     * @tparam T 
     */
    template<typename T>
    class ValueUniverse{
    public:
        ValueUniverse(llvm::Function*);
        ValueUniverse(std::vector<T> e);

        int Size();
        std::vector<T> ToArray();

        /**
         * @brief 
         *  Input Iterator for ValueUniverse
         *  check http://www.cplusplus.com/reference/iterator/ to know what functionalities input iterator provides
         */
        class Iterator{
            public:
                typedef Iterator self_type;
                typedef T value_type;
                typedef T& reference;
                typedef T* pointer;
                typedef std::input_iterator_tag iterator_category;

                Iterator():_ptr(nullptr),avu(nullptr),idx(-1){};
                Iterator(ValueUniverse<T>* b){
                    _ptr = &b->ele[0];
                    avu = b;
                    idx = 0;
                }
                Iterator(const Iterator& cit):avu(cit.avu),_ptr(cit._ptr),idx(cit.idx){}
                Iterator& operator++(){
                    if(_ptr == nullptr)
                        return *this;
                    ++_ptr,++idx;
                    if(idx >= avu->ele.size()){
                        _ptr = nullptr;
                        return *this;
                    }
                    return *this;
                }
                Iterator operator++(int){
                    self_type tmp(*this);
                    if(_ptr)
                        operator++();
                    return tmp;
                }
                bool operator==(const Iterator& rhs) const{
                    return _ptr == rhs._ptr;
                }
                bool operator!=(const Iterator& rhs) const{
                    return _ptr != rhs._ptr;
                }
                reference operator*(){
                    return avu->ele[idx];
                }
                pointer operator->(){
                    return &(avu->ele[idx]);
                }
                ~Iterator(){}
            private:
                pointer _ptr;
                ValueUniverse<T>* avu;
                int idx;
        };

        Iterator begin();
        Iterator end();

    private:
        std::vector<T> ele;
    };
}

#endif