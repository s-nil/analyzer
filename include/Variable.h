#ifndef _A_VARIABLE_H_
#define _A_VARIABLE_H_
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"

namespace A{
    class Variable{
    public:
        Variable(llvm::Value* v){
            id = (long)v;
            value = v;
        }
        llvm::Value* GetValue();
        void SetValue(llvm::Value*);
        ~Variable(){}

        bool operator==(const Variable& rhs) const{
            return value == rhs.value;
        }
        bool operator!=(const Variable& rhs) const{
            return value != rhs.value;
        }

        bool operator<(const Variable& rhs) const{
            return rhs.id < this->id; 
        }

        friend llvm::raw_ostream& operator<<(llvm::raw_ostream& out, Variable& v){
            out << (v.value)->getName();
            return out;
        }
    private:
        long id;
        llvm::Value* value;
    };
}

#endif