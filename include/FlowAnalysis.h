/**
 * @file FlowAnalysis.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _A_FLOW_ANALYSIS_H_
#define _A_FLOW_ANALYSIS_H_

#include "AbstractFlowAnalysis.h"

namespace A{
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template<typename T>
    class FlowAnalysis{
    public:
        FlowAnalysis(){}
        ~FlowAnalysis(){}

        T NewInitialFlowSet();
        T EntryInitialFlowSet();
        void Merge(T in1, T in2, T out);
        void Copy(T in1, T in2);
        T GetFlowBefore(llvm::BasicBlock* node);
        void doAnalysis();
    };

template class A::AbstractFlowAnalysis<int>;
template class A::AbstractFlowAnalysis<char*>;
}

#endif