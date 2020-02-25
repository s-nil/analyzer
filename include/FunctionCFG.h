/**
 * @file FunctionCFG.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _A_FUNCTION_CFG_H_
#define _A_FUNCTION_CFG_H_
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/CFG.h"
#include <list>
#include <vector>
#include <stack>

namespace A{
    enum Direction{FORWARD,BACKWARD};
    /**
     * @brief 
     * 
     */
    class Node{
        unsigned id;
        llvm::BasicBlock* bb;
        std::vector<llvm::BasicBlock*> preds;
        std::vector<llvm::BasicBlock*> succs;
    public:
        Node();
        Node(llvm::BasicBlock* node,unsigned n){
            id = n;
            this->bb = node;
            preds = std::vector<llvm::BasicBlock*>(0);
            succs = std::vector<llvm::BasicBlock*>(0);

            if(bb)
                for(llvm::succ_iterator itb = succ_begin(bb),ite=succ_end(bb); itb!=ite; ++itb)
                    succs.push_back(*itb);
                
            if(bb)
                for(llvm::pred_iterator itb = pred_begin(bb),ite=pred_end(bb); itb!=ite; ++itb)
                    preds.push_back(*itb);
        }
        std::string GetName(){return bb->getName().str();}
        llvm::BasicBlock* GetBB(){return bb;}
        std::vector<llvm::BasicBlock*> GetPreds(){return preds;}
        int PredCount(){return preds.size();}
        std::vector<llvm::BasicBlock*> GetSuccs(){return succs;}
        int SuccsCount(){return succs.size();}
    };
    /**
     * @brief 
     * 
     */
    class FunctionCFG{
    public:
        FunctionCFG(llvm::Function*);
        ~FunctionCFG(){}

        Node* GetNode(llvm::BasicBlock* bb){   return BBtoNode[bb];}
        std::vector<llvm::BasicBlock*> GetHeads();
        std::vector<llvm::BasicBlock*> GetTails();
        std::vector<Node*> GetHeadsN();
        std::vector<Node*> GetTailsN();
        std::vector<llvm::BasicBlock*> GetIn(A::Node*,Direction);
        std::vector<llvm::BasicBlock*> GetOut(A::Node*,Direction);
        std::vector<Node*> GetInN(A::Node*,Direction);
        std::vector<Node*> GetOutN(A::Node*,Direction);
    private:
        unsigned NumBB;
        std::vector<Node*> *Nodes;
        llvm::DenseMap<llvm::BasicBlock*,Node*> BBtoNode;
        llvm::Function* func;
    };
    
}

#endif