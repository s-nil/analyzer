#ifndef _BASE_H_
#define _BASE_H_

namespace L
{
    template<typename T>
    class Base
    {
    private:
        T data;
    public:
        Base(){}
        Base(T d)
        {
            data = d;
        }

        ~Base();

        void set(const T& val);
        T& get();
        void print();
    };    
}

#endif