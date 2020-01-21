#ifndef _A_OBJECT_INT_MAPPER_H_
#define _A_OBJECT_INT_MAPPER_H_
#include <vector>
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/raw_ostream.h"

namespace A
{
    template<typename T>
    class ObjectIntMapper
    {
    public:
        ObjectIntMapper(){
            intToObject = std::vector<int>();
            objectToInt = llvm::DenseMap<T,int>();
            counter = 0;
        }
        ~ObjectIntMapper(){}

        int Add(T obj);
        int GetInt(T obj);
        T GetObject(int idx);
        bool Contains(T obj);
        int Size();

    private:
        std::vector<T> intToObject;
        int counter;
        llvm::DenseMap<T,int> objectToInt; 

    };    
}

#endif