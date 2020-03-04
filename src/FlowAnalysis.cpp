#include "FlowAnalysis.h"
#include "llvm/Support/raw_ostream.h"
#include "ArrayPackedSet.h"
#include "ArraySparseSet.h"

template<typename T>
inline T* A::FlowAnalysis<T>::GetFlowBefore(llvm::BasicBlock* node){    return inSet[node];}

template<typename T>
inline T* A::FlowAnalysis<T>::GetFlowAfter(llvm::BasicBlock* node){ return outSet[node];}

template<typename T>
inline llvm::DenseMap<llvm::BasicBlock*,T*> A::FlowAnalysis<T>::GetIn(){    return inSet;}

template<typename T>
inline llvm::DenseMap<llvm::BasicBlock*,T*> A::FlowAnalysis<T>::GetOut(){   return outSet;}

template<typename T>
inline void A::FlowAnalysis<T>::SetFlowBefore(llvm::BasicBlock* node, T* d){    inSet[node] = d;}

template<typename T>
inline void A::FlowAnalysis<T>::SetFlowAfter(llvm::BasicBlock* node, T* d){ outSet[node] = d;}

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
    while (!queueNodes.empty()){
        A::NodeData<T>* node = queueNodes.front();
        queueNodes.pop();

        auto tmpOut = node->GetOutFlow()->Clone();
        auto tmpIn = node->GetInFlow()->Clone();
        
        if(node->GetINcomingN().size() < 0)
            continue;

        /// Merge
        if(node->GetINcomingN().size() > 1){
            bool copy = false;
            for (unsigned i = 0; i < node->GetINcomingN().size(); ++i){
                auto outFlow = node->GetINcomingN()[i]->GetOutFlow();
                if(!copy)
                    this->Copy(outFlow,node->GetInFlow()), copy = true;
                else{
                    auto tmp = this->NewInitialFlowSet();
                    /// using overriden Merge and Copy
                    this->Merge(outFlow,node->GetInFlow(),tmp);
                    this->Copy(tmp,node->GetInFlow());
                }
            }
        }
        
        this->FlowThrough(node->GetNode(),node->GetInFlow(),node->GetOutFlow());
        
        if(!node->GetOutFlow()->Equals(tmpOut))
            queueNodes.push(node);

        if(!node->GetInFlow()->Equals(tmpIn))
            queueNodes.push(node);
    }

    PrintResult(lstNodes);
}

template<typename T>
void A::FlowAnalysis<T>::PrintResult(std::vector<A::NodeData<T>*>& lstNodes){
    for(A::NodeData<T>* u : lstNodes){
        llvm::errs() <<"Basic Block : "<< u->GetNodeName() << '\n';

        llvm::errs()<<" In   :: ";
        for(auto x : *u->GetInFlow()){
            llvm::errs() << x << ", ";
        }
        llvm::errs()<<'\n';

        llvm::errs()<<" Out  :: ";
        for(auto x : *u->GetOutFlow()){
            llvm::errs() << x << ", ";
        }
        llvm::errs()<<'\n';
        llvm::errs()<<'\n';
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

/**
 * @brief 
 * 
 * @tparam T 
 * @param lstNodes 
 */
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

template class A::FlowAnalysis<A::ArrayPackedSet<A::Variable>>;
template class A::FlowAnalysis<A::ArraySparseSet<A::Variable>>;