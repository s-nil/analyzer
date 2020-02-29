/**
 * @file ObjectIntMapper.h
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _A_OBJECT_INT_MAPPER_H_
#define _A_OBJECT_INT_MAPPER_H_
#include <vector>
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/raw_ostream.h"
#include "ValueUniverse.h"
#include "llvm/IR/Value.h"
#include <map>

namespace A
{
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template<typename T>
    class ObjectIntMapper
    {
    public:
        ObjectIntMapper(){
            intToObject = std::vector<T>();
            objectToInt = std::map<T,int>();
            counter = 0;
        }
        
        ObjectIntMapper(ValueUniverse<T>& values){
            intToObject = std::vector<T>();
            objectToInt = std::map<T,int>();
            counter = 0;

            for(auto I = values.begin(), IE = values.end(); I != IE; ++I){
                Add(*I);
            }
            
        }
        ~ObjectIntMapper(){}

        int Add(T obj);
        int GetInt(T obj);
        T GetObject(int idx);
        bool Contains(T obj);
        int Size();

        bool operator==(ObjectIntMapper<T> rhs);
        bool operator!=(ObjectIntMapper<T> rhs); 
    private:
        std::vector<T> intToObject;
        int counter;
        // llvm::DenseMap<T,int> objectToInt; 
        std::map<T,int> objectToInt;
    };    
}

#endif