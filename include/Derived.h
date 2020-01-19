#ifndef _DERIVED_H_
#define _DERIVED_H_

#include "Base.h"

namespace L
{
    template<typename T>
    class Derived : public Base<T>
    {
        public:
            Derived(){}
            Derived(T v) : Base<T>(v){}

            void set(const T& val);
            T& get();
    };
}

#endif