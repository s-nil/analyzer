#include "FunctionCFG.h"
#include "llvm/ADT/DepthFirstIterator.h"

/**
 * @brief Construct a new A:: Function C F G:: Function C F G object
 * 
 * @param f 
 */
A::FunctionCFG::FunctionCFG(llvm::Function* f){
    this->NumBB = f->size();
    this->func  = f;
    Nodes = new std::vector<Node*>();

    for (llvm::df_iterator<llvm::BasicBlock*> I = llvm::df_begin(&func->getEntryBlock()),
                                            IE=llvm::df_end(&func->getEntryBlock()); I != IE; ++I){
        A::Node* node = new A::Node(*I,Nodes->size());
        BBtoNode[*I] = node;
        Nodes->push_back(node);
    }
}

/**
 * @brief 
 * 
 * @return std::vector<llvm::BasicBlock*> 
 */
std::vector<llvm::BasicBlock*> A::FunctionCFG::GetHeads(){
    std::vector<llvm::BasicBlock*> lst;
    for(auto node : *Nodes){
        if(!node->PredCount()){
            lst.push_back(node->GetBB());
        }
    }
    return lst;
}

/**
 * @brief 
 * 
 * @return std::vector<llvm::BasicBlock*> 
 */
std::vector<llvm::BasicBlock*> A::FunctionCFG::GetTails(){
    std::vector<llvm::BasicBlock*> lst;
    for(auto node : *Nodes){
        if(!node->SuccsCount()){
            lst.push_back(node->GetBB());
        }
    }
    return lst;
}
        
/**
 * @brief 
 * 
 * @return std::vector<A::Node*> 
 */
std::vector<A::Node*> A::FunctionCFG::GetHeadsN(){
    std::vector<A::Node*> lst;
    for(auto node : *Nodes){
        if(!node->PredCount()){
            lst.push_back(node);
        }
    }
    return lst;    
}

/**
 * @brief 
 * 
 * @return std::vector<A::Node*> 
 */
std::vector<A::Node*> A::FunctionCFG::GetTailsN(){
    std::vector<A::Node*> lst;
    for(auto node : *Nodes){
        if(!node->SuccsCount()){
            lst.push_back(node);
        }
    }
    return lst;    
}

/**
 * @brief 
 * 
 * @param n 
 * @param dir 
 * @return std::vector<llvm::BasicBlock*> 
 */
std::vector<llvm::BasicBlock*> A::FunctionCFG::GetIn(A::Node* n,Direction dir){
    if(dir == Direction::FORWARD){
        return n->GetPreds();
    }else{
        return n->GetSuccs();
    }
}

/**
 * @brief 
 * 
 * @param n 
 * @param dir 
 * @return std::vector<llvm::BasicBlock*> 
 */
std::vector<llvm::BasicBlock*> A::FunctionCFG::GetOut(A::Node* n,Direction dir){
    if(dir == Direction::FORWARD){
        return n->GetSuccs();
    }else{
        return n->GetPreds();
    }
}

/**
 * @brief 
 * 
 * @param n 
 * @param dir 
 * @return std::vector<A::Node*> 
 */
std::vector<A::Node*> A::FunctionCFG::GetInN(A::Node* n,Direction dir){
    std::vector<A::Node*> lst;
    if(dir == Direction::FORWARD){
        std::transform(n->GetPreds().begin(),n->GetPreds().end(),std::inserter(lst,lst.begin()),[this](llvm::BasicBlock* bb){return GetNode(bb);});
    }else{
        std::transform(n->GetSuccs().begin(),n->GetSuccs().end(),std::inserter(lst,lst.begin()),[this](llvm::BasicBlock* bb){return GetNode(bb);});
    }
    return lst;
}

/**
 * @brief 
 * 
 * @param n 
 * @param dir 
 * @return std::vector<A::Node*> 
 */
std::vector<A::Node*> A::FunctionCFG::GetOutN(A::Node* n,Direction dir){
    std::vector<A::Node*> lst;
    if(dir == Direction::FORWARD){
        std::transform(n->GetSuccs().begin(),n->GetSuccs().end(),std::inserter(lst,lst.begin()),[this](llvm::BasicBlock* bb){return GetNode(bb);});
    }else{
        std::transform(n->GetPreds().begin(),n->GetPreds().end(),std::inserter(lst,lst.begin()),[this](llvm::BasicBlock* bb){return GetNode(bb);});
    }
    return lst;    
}