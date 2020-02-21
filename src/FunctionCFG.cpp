#include "FunctionCFG.h"
#include "llvm/ADT/DepthFirstIterator.h"

A::FunctionCFG::FunctionCFG(llvm::Function* f){
    this->NumBB = f->size();
    this->func  = f;
    Nodes = new std::vector<Node*>(0);

    DFS();
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

void A::FunctionCFG::DFS(){
    llvm::BasicBlock* bb = &func->getEntryBlock();
    llvm::DenseMap<llvm::BasicBlock*,bool> visited;
    std::stack<llvm::BasicBlock*> stk;
    stk.push(bb);

    while (!stk.empty()){
        auto s = stk.top();
        stk.pop();
        if(!visited[s]){
            // llvm::errs() << s->getName().str()<<'\n';
            A::Node* node = new A::Node(s,Nodes->size());
            Nodes->push_back(node);
            visited[s] = 1;
        }
        for(llvm::succ_iterator itb = succ_begin(s),ite=succ_end(s); itb!=ite; ++itb){
            if(!visited[*itb]){
                stk.push(*itb);
            }
        }
    }
}