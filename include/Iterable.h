/**
 * @file IterableList.h
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _A_ITERABLE_H_
#define _A_ITERABLE_H_

#include <iostream>
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"

using namespace std;

namespace A{

template<typename T>
class Iterable
{
public:
    virtual Iterable& operator=(T n) = 0;
    virtual Iterable& operator++() = 0;
    virtual Iterable& operator++(int) = 0;
    virtual bool operator!=(const Iterable& it) = 0;
    virtual bool operator==(const Iterable& it) = 0;
    virtual T operator*() = 0;
private:
};

}   //  

#endif  // 
