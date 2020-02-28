#include "FlowAnalysis.h"
#include "llvm/Support/raw_ostream.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"

/**
 * @brief 
 * 
 * @tparam T 
 * @param node 
 * @return T* 
 */
template<typename T>
inline T* A::FlowAnalysis<T>::GetFlowBefore(llvm::BasicBlock* node){
    return finalInSet[node];
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param node 
 * @return T* 
 */
template<typename T>
inline T* A::FlowAnalysis<T>::GetFlowAfter(llvm::BasicBlock* node){
    return finalOutSet[node];
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param node 
 * @param d 
 */
template<typename T>
inline void A::FlowAnalysis<T>::SetFlowBefore(llvm::BasicBlock* node, T* d){
    finalInSet[node] = d;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param node 
 * @param d 
 */
template<typename T>
inline void A::FlowAnalysis<T>::SetFlowAfter(llvm::BasicBlock* node, T* d){
    finalOutSet[node] = d;
}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::FlowAnalysis<T>::Compute(){
    llvm::Function* func = this->func;
    std::vector<A::NodeData<T>*> lstNodes = NodesDataList();

    InitializeFlows(lstNodes);
    
    std::queue<A::NodeData<T>*> queueNodes;
    for (auto& e : lstNodes){
        queueNodes.push(e);
    }
    
    // fixed point analysis
    // Not complete yet
    while (!queueNodes.empty()){
        A::NodeData<T>* node = queueNodes.front();
        queueNodes.pop();

        if(node->GetINcomingN().size() < 0)
            continue;

        if(node->GetINcomingN().size() > 1){
            llvm::errs() <<":"<< node->GetINcomingN().size()<<" "<<node->GetInFlow() <<" "<<node->GetOutFlow() << " " << node->GetNodeName() <<"\n";
            
            bool copy = false;
            for (unsigned i = 0; i < node->GetINcomingN().size(); ++i){
                auto outFlow = node->GetINcomingN()[i]->GetOutFlow();
                // auto outFlow = n->GetOutFlow();
                if(!copy)
                    this->Copy(outFlow,node->GetInFlow()), copy = true;
                else{
                    auto tmp = this->NewInitialFlowSet();
                    this->Merge(outFlow,node->GetInFlow(),tmp);
                    this->Copy(tmp,node->GetInFlow());
                }
            }
        }else{
            llvm::errs() << node->GetINcomingN().size()<<" "<<node->GetInFlow() <<" "<<node->GetOutFlow() << " " << node->GetNodeName() <<"\n";
        }
        
        this->FlowThrough(node->GetNode(),node->GetInFlow(),node->GetOutFlow());
        
    }
        
}

/**
 * @brief 
 * 
 * @tparam T 
 * @return std::vector<A::NodeData<T>*> 
 */
template<typename T>
std::vector<A::NodeData<T>*> A::FlowAnalysis<T>::NodesDataList(){
    std::vector<A::NodeData<T>*> l;
    
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
    auto tmp = this->EntryInitialFlowSet();
    dummyEntry->SetInFlow(tmp);
    dummyEntry->SetOutFlow(tmp);

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
        if(s->GetNode())
            l.push_back(s);
    }

    return l;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param visited 
 * @param blocks 
 * @param nd 
 */
template<typename T>
void A::FlowAnalysis<T>::AddOutData(llvm::DenseMap<llvm::BasicBlock*,A::NodeData<T>*>& visited, 
                                                std::vector<llvm::BasicBlock*>& blocks, A::NodeData<T>* nd){
    llvm::SmallVector<A::NodeData<T>*,0> out;
    
    for(unsigned i=0; i<blocks.size(); ++i){
        out.push_back(CreateAndReturnNodeData(visited,blocks[i],nd));
    }
    nd->AddOut(out);
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param visited 
 * @param entry 
 * @param node 
 * @return A::NodeData<T>* 
 */
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

template<typename T>
void A::FlowAnalysis<T>::InitializeFlows(std::vector<A::NodeData<T>*>& lstNodes){
    for (auto I = lstNodes.begin(), IE = lstNodes.end(); I != IE; ++I){
        if((*I)->GetINcomingN().size() > 1){
            auto tmp = this->NewInitialFlowSet();
            (*I)->SetInFlow(tmp);
        }else if((*I)->GetINcomingN().size() == 1){
            // if node has only one predeccesor then same node
            auto tmp = this->NewInitialFlowSet();
            if(!(*I)->GetINcomingN()[0]->GetOutFlow())
                (*I)->GetINcomingN()[0]->SetOutFlow(tmp);
            (*I)->SetInFlow((*I)->GetINcomingN()[0]->GetOutFlow());
        }
        auto tmp = this->NewInitialFlowSet();
        (*I)->SetOutFlow(tmp);

        SetFlowBefore((*I)->GetNode(),(*I)->GetInFlow());
        SetFlowAfter((*I)->GetNode(),(*I)->GetOutFlow());
    }
}

template class A::FlowAnalysis<A::ArrayPackedSet<char*>>;
template class A::FlowAnalysis<A::ArraySparseSet<char*>>;
template class A::FlowAnalysis<A::ArrayPackedSet<A::Variable*>>;
template class A::FlowAnalysis<A::ArraySparseSet<A::Variable*>>;