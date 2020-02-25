#include "FlowAnalysis.h"
#include "llvm/Support/raw_ostream.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"

/**
 * @brief 
 * 
 * @tparam T 
 * @param node 
 * @return T 
 */
template<typename T>
T A::FlowAnalysis<T>::GetFlowBefore(llvm::BasicBlock* node){

}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::FlowAnalysis<T>::Compute(){
    // llvm::Function* func = this->func;
    std::vector<A::NodeData<T>*> lstNodes = NodesDataList();
}

template<typename T>
std::vector<A::NodeData<T>*> A::FlowAnalysis<T>::NodesDataList(){
    std::vector<A::NodeData<T>*> l;
    llvm::errs() << this->func->size() <<'\n';
    
    std::vector<llvm::BasicBlock*> entries;
    A::FunctionCFG* g = this->graph;
    if(this->IsForward()){
        entries = g->GetHeads();
    }else{
        entries = g->GetTails();
    }

    llvm::DenseMap<llvm::BasicBlock*,A::NodeData<T>*> visited;
    int n = -1;
    A::NodeData<T> *dummyEntry = new A::NodeData<T>();

    AddOutData(visited,entries,dummyEntry);
    dummyEntry->MarkVisit(++n);
    dummyEntry->SetInFlow(this->EntryInitialFlowSet());
    dummyEntry->SetOutFlow(this->EntryInitialFlowSet());

    std::stack<A::NodeData<T>*> visitStack;
    unsigned i = 0;
    A::NodeData<T> *v = dummyEntry;
    visitStack.push(dummyEntry);

    while(!visitStack.empty()){
        A::NodeData<T>* s = visitStack.top();
        visitStack.pop();

        if(!s->IsVisited()){
            s->MarkVisit(++n);
            std::vector<llvm::BasicBlock*> outs = g->GetOut(g->GetNode(s->GetNode()),A::Direction::BACKWARD);
            AddOutData(visited,outs,s);
        }

        llvm::SmallVector<A::NodeData<T>*,0> tmp = s->GetOutgoingN();
        for(auto i=0; i<tmp.size(); ++i){
            A::NodeData<T>* w  = tmp[i];
            if(!w->IsVisited())
            visitStack.push(w);
        }
        l.push_back(s);
    }

    return l;
}

template<typename T>
void A::FlowAnalysis<T>::AddOutData(llvm::DenseMap<llvm::BasicBlock*,A::NodeData<T>*>& visited, 
                                                std::vector<llvm::BasicBlock*>& blocks, A::NodeData<T>* nd){
    llvm::SmallVector<A::NodeData<T>*,0> out;
    
    for(unsigned i=0; i<blocks.size(); ++i){
        out.push_back(CreateAndReturnNodeData(visited,blocks[i],nd));
    }
    nd->AddOut(out);
}


template<typename T>
A::NodeData<T>* A::FlowAnalysis<T>::CreateAndReturnNodeData(llvm::DenseMap<llvm::BasicBlock*,A::NodeData<T>*>& visited, 
                                                        llvm::BasicBlock* entry, A::NodeData<T> *node){
    if(!visited[entry]){
        A::NodeData<T> *nd = new A::NodeData<T>(entry,node);
        visited[entry] = nd;
        return nd;
    }else{
        A::NodeData<T> *oldNodeData = visited[entry];
        if(oldNodeData != node)
            oldNodeData->AddIn(node);
        return oldNodeData;
    }
}

template class A::FlowAnalysis<A::ArrayPackedSet<char*>>;
template class A::FlowAnalysis<A::ArraySparseSet<char*>>;