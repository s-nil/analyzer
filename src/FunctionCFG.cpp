#include "FunctionCFG.h"
#include "llvm/ADT/DepthFirstIterator.h"

A::FunctionCFG::FunctionCFG(llvm::Function* f){
    this->NumBB = f->size();
    this->func  = f;
    Nodes = new std::vector<Node*>(0);

    for (llvm::df_iterator<llvm::BasicBlock*> I = llvm::df_begin(&func->getEntryBlock()),
                                            IE=llvm::df_end(&func->getEntryBlock()); I != IE; ++I){
        A::Node* node = new A::Node(*I,Nodes->size());
        Nodes->push_back(node);
    }
}

std::list<llvm::BasicBlock*> A::FunctionCFG::GetHeads(){
    std::list<llvm::BasicBlock*> lst;
    for(auto node : *Nodes){
        if(!node->PredCount()){
            lst.push_back(node->GetBB());
        }
    }
    return lst;    
}

std::list<llvm::BasicBlock*> A::FunctionCFG::GetTails(){
    std::list<llvm::BasicBlock*> lst;
    for(auto node : *Nodes){
        if(!node->SuccsCount()){
            lst.push_back(node->GetBB());
        }
    }
    return lst;    
}

std::list<llvm::BasicBlock*> A::FunctionCFG::GetIn(A::Node* n,Direction dir){
    std::list<llvm::BasicBlock*> lst;
    if(dir == Direction::FORWARD){
        std::copy(n->GetPreds().begin(),n->GetPreds().end(),std::back_inserter(lst));
    }else{
        std::copy(n->GetSuccs().begin(),n->GetSuccs().end(),std::back_inserter(lst));
    }
    return lst;
}

std::list<llvm::BasicBlock*> A::FunctionCFG::GetOut(A::Node* n,Direction dir){
    std::list<llvm::BasicBlock*> lst;
    if(dir == Direction::FORWARD){
        std::copy(n->GetSuccs().begin(),n->GetSuccs().end(),std::back_inserter(lst));
    }else{
        std::copy(n->GetPreds().begin(),n->GetPreds().end(),std::back_inserter(lst));
    }
    return lst;    
}