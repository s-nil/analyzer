/**
 * @file NodeData.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _A_NODE_DATA_H_
#define _A_NODE_DATA_H_
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"

namespace A{
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template<typename T>
    class NodeData{
    public:
        NodeData(){
            node = nullptr;
            number = INT_MIN;
            inFlow = nullptr;
            outFlow = nullptr;
        }
        NodeData(llvm::BasicBlock* n, NodeData<T>* in){
            node = n;
            if(in) AddIn(in);
            number = INT_MIN;
            inFlow = nullptr;
            outFlow = nullptr;
        }
        std::string GetNodeName();
        T* GetInFlow(){     return inFlow;}
        T* GetOutFlow(){    return outFlow;}
        void SetInFlow(T* in){    inFlow = in;}
        void SetOutFlow(T* out){  outFlow = out;}
        llvm::SmallVector<NodeData<T>*,0> GetINcomingN(){    return incoming;}
        llvm::SmallVector<NodeData<T>*,0> GetOutgoingN(){    return outgoing;}
        llvm::BasicBlock* GetNode(){    /*if(node)llvm::errs() << ":: "<<node->getName().str()<<'\n';*/ return node;}
        llvm::SmallVector<llvm::BasicBlock*,0> GetINcoming();
        llvm::SmallVector<llvm::BasicBlock*,0> GetOutgoing();
        void AddIn(NodeData<T>*);
        void AddIn(llvm::SmallVector<NodeData<T>*,0>);
        void AddOut(NodeData<T>*);
        void AddOut(llvm::SmallVector<NodeData<T>*,0>);
        bool IsVisited(){  return number != INT_MIN;}
        void MarkVisit(int n){   number=n;}
        ~NodeData(){}
    private:
        llvm::BasicBlock* node;
        /// final in flow after merging all incoming flow data
        T* inFlow;
        /// out flow after applying transfer function to the inFlow
        T* outFlow;
        /// data of incoming edges
        llvm::SmallVector<NodeData<T>*,0>  incoming;
        /// data of outgoing edges
        llvm::SmallVector<NodeData<T>*,0>  outgoing;
        ///
        int number;
    };
    
}

#endif