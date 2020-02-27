/**
 * @file BackwardFlowAnalysis.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _A_BACKWARD_FLOW_ANALYSIS_H_
#define _A_BACKWARD_FLOW_ANALYSIS_H_
#include "FlowAnalysis.h"

namespace A{
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template<typename T>
    class BackwardFlowAnalysis : public FlowAnalysis<T>{
    public:
        BackwardFlowAnalysis(){}
        ~BackwardFlowAnalysis(){}

        void DoAnalysis() override;
        bool IsForward() override;
    private:
    };    
}

#endif