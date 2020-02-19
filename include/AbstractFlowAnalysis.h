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

namespace A{
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template<typename T>
    class AbstractFlowAnalysis{
    public:
        virtual ~AbstractFlowAnalysis(){}
        
        virtual T NewInitialFlowSet() = 0;
        virtual T EntryInitialFlowSet() = 0;
        virtual void Merge(T in1, T in2, T out) = 0;
        virtual void Copy(T in1, T in2) = 0;
        virtual T GetFlowBefore(llvm::BasicBlock* node) = 0;
        virtual void doAnalysis() = 0;

    private:
        llvm::DenseMap<llvm::BasicBlock*,T> finalInSet;
    };
}

#endif