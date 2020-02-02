#ifndef _A_ARRAY_VALUSE_UNIVERSE_H_
#define _A_ARRAY_VALUSE_UNIVERSE_H_
#include "ValueUniverse.h"
#include <iterator>

namespace A{
    /**
     * @brief 
     *  An implementation of the domain that'll be used in bounded set
     * @tparam T 
     */
    template<typename T>
    class ArrayValueUniverse : public ValueUniverse<T>{
    public:
        ArrayValueUniverse(std::vector<T> e);

        int Size();
        std::vector<T> ToArray();

        /**
         * @brief 
         *  Input Iterator for ArrayValueUniverse
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
                Iterator(ArrayValueUniverse<T>* b){
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
                ArrayValueUniverse<T>* avu;
                int idx;
        };

        Iterator begin();
        Iterator end();

    private:
        std::vector<T> ele;
    };
}

#endif