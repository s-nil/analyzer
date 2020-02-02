#ifndef _A_VALUE_UNIVERSE_H_
#define _A_VALUE_UNIVERSE_H_
#include <vector>

namespace A{
    /**
     * @brief 
     *  Interface, providing functions for the domain
     * @tparam T 
     */
    template<typename T>
    class ValueUniverse{
    public:
        ValueUniverse(){}
        ~ValueUniverse(){}

        virtual int Size() = 0;
        virtual std::vector<T> ToArray() = 0;
    };
}

#endif
