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
#include "NodeData.h"
#include <list>
#include <stack>
#include "llvm/ADT/SmallVector.h"
#include <queue>

namespace A{
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template<typename T>
    class FlowAnalysis : public AbstractFlowAnalysis<T>{
    public:
        FlowAnalysis(){}
        ~FlowAnalysis(){}

        T* GetFlowBefore(llvm::BasicBlock*);
        T* GetFlowAfter(llvm::BasicBlock*);
        void SetFlowBefore(llvm::BasicBlock* node, T*);
        void SetFlowAfter(llvm::BasicBlock* node, T*);
        void Compute();
    private:
        std::vector<A::NodeData<T>*> NodesDataList();
        void AddOutData(llvm::DenseMap<llvm::BasicBlock*,A::NodeData<T>*>&, 
                                                        std::vector<llvm::BasicBlock*>&, A::NodeData<T>*);
        A::NodeData<T>* CreateAndReturnNodeData(llvm::DenseMap<llvm::BasicBlock*,A::NodeData<T>*>&, 
                                                        llvm::BasicBlock*, A::NodeData<T>*);
        void InitializeFlows(std::vector<A::NodeData<T>*>&);

        llvm::DenseMap<llvm::BasicBlock*,T*> finalInSet;
        llvm::DenseMap<llvm::BasicBlock*,T*> finalOutSet;
    };
}

#endif