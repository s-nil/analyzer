/**
 * @file AbstractFlowAnalysis.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _A_ABSTRACT_FLOW_ANALYSIS_H_
#define _A_ABSTRACT_FLOW_ANALYSIS_H_

#include "llvm/IR/Function.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/raw_ostream.h"
#include "FunctionCFG.h"

namespace A{
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template<typename T>
    class AbstractFlowAnalysis{
    public:
        AbstractFlowAnalysis():func(nullptr),graph(nullptr){}
        virtual ~AbstractFlowAnalysis(){}
        
        virtual T* NewInitialFlowSet() = 0;
        virtual T* EntryInitialFlowSet() = 0;
        virtual void Merge(T* in1, T* in2, T* out) = 0;
        virtual void Copy(T* in1, T* in2) = 0;
        virtual void FlowThrough(llvm::BasicBlock* node, T* in, T* out) = 0;
        virtual void DoAnalysis() = 0;
        virtual bool IsForward() = 0;
        void SetFunction(llvm::Function*);
    protected:
        llvm::Function* func;
        A::FunctionCFG* graph;
    };
}

#endif