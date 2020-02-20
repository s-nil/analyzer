#ifndef _A_NODE_DATA_H_
#define _A_NODE_DATA_H_
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/BasicBlock.h"

namespace A{
    template<typename T>
    class NodeData{
    public:
        NodeData(){
            node = nullptr;
        }
        NodeData(llvm::BasicBlock* n){
            node = n;
        }
        inline std::string GetNodeName();
        inline T GetInFlow();
        inline T GetOutFlow();
        ~NodeData(){}
    private:
        llvm::BasicBlock* node;
        T inFlow;
        T outFlow;
        llvm::SmallVector<NodeData*,0>  in;
        llvm::SmallVector<NodeData*,0>  out;
    };
    
}

#endif