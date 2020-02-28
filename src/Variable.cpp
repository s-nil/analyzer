#include "Variable.h"

inline llvm::Value* A::Variable::GetValue(){
    return value;
}

inline void A::Variable::SetValue(llvm::Value* v){
    value = v;
}