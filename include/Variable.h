#ifndef _A_VARIABLE_H_
#define _A_VARIABLE_H_
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"

namespace A{
    class Variable{
    public:
        Variable(llvm::Value* v){
            value = v;
        }
        llvm::Value* GetValue();
        void SetValue(llvm::Value*);
        ~Variable(){}

        bool operator==(const Variable& rhs){
            return value == rhs.value;
        }
        bool operator!=(const Variable& rhs){
            return value != rhs.value;
        }

        friend llvm::raw_ostream& operator<<(llvm::raw_ostream& out, Variable* v){
            out << v->value;
            return out;
        }
    private:
        llvm::Value* value;
    };
}

#endif