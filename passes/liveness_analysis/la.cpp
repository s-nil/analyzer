/**
 * @file pass1.cpp
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Demangle/Demangle.h"

#include "framework.h"
#include <sstream>

class Variable{
public:
    Variable(llvm::Value* v):id((long)v),value(v){	}
    llvm::Value* GetValue(){return value;}
    void SetValue(llvm::Value* v){value = v;}
    ~Variable(){}

    bool operator==(const Variable& rhs) const{	return value == rhs.value;}
    bool operator!=(const Variable& rhs) const{	return value != rhs.value;}

    bool operator<(const Variable& rhs) const{	return rhs.id < this->id; }

    friend llvm::raw_ostream& operator<<(llvm::raw_ostream& out, Variable& v){
        out << (v.value)->getName();return out;
    }
	friend std::stringstream& operator<<(std::stringstream& out, const Variable& v){
          out << (v.value)->getName().str(); return out;
    }
private:
    long id;
    llvm::Value* value;
};

EXTRACT(Variable){
//template<>
//A::ValueUniverse<Variable>::ValueUniverse(Function* f){
    //errs() << f->getName()<<'\n';
    bool noCallSite = 1;
    elements = std::vector<Variable>();
    for (auto I = f->arg_begin(); I != f->arg_end(); ++I){
        Variable var = Variable(I);
        elements.push_back(var);
    }
    for (llvm::inst_iterator I = llvm::inst_begin(*f); I != llvm::inst_end(*f); ++I){
        llvm::CallSite cs(&*I);
        if(cs.getInstruction() && !(*I).isLifetimeStartOrEnd()){
            noCallSite = 0;
            llvm::errs() << *I << '\n';
            break;
        }
        if((*I).isLifetimeStartOrEnd()){
            continue;
        }
        if((*I).hasName()){
            llvm::Value* v = &*I;
            Variable var = Variable(v);
            elements.push_back(var);
        }
    }
    if(!(noCallSite == 1)){
        llvm::errs() << RED <<"Assertion : a function call is found.\n" << RESET <<'\n';
        exit(1);
    }
}

namespace {
    BACKWARDANALYSIS(LA,BoundedSet,Variable){
        static char ID;
        string funcName;
        BoundedSet<Variable> *domain;
 
        LA(string f): funcName(f), FunctionPass(ID){}
        
        RUN(){
			SETUP_FUNCTION();
            //if(demangleName(F).substr(0,funcName.size()).compare(funcName) != 0)
            //    return false;
			errs() << "function name: " << demangleName(F) << '\n';

            domain = new BoundedSet<Variable>(&F);
            DoAnalysis();
            return false;
        }

        BS_INITIALVALUE(){	return domain->EmptySet();}

        BS_ENTRYVALUE(){	return domain->EmptySet();}

		BS_MERGE(Variable){	in1->Union(in2,out);}

		BS_COPY(Variable){	in1->Copy(in2);}
        
		BS_FLOWTH(Variable){
            BoundedSet<Variable>* def = domain->EmptySet();
            BoundedSet<Variable>* use = domain->EmptySet();
            
            if(&func->getEntryBlock() == node && func->arg_size()>0){
                for(auto arg_it=func->arg_begin(); arg_it != func->arg_end(); ++arg_it){
                    def->Add(arg_it);
                }
            }

            for(auto I=node->begin(),IE=node->end(); I!=IE; ++I){
                if((*I).isLifetimeStartOrEnd()){
                    continue;
                }
                
                for (auto J = 0; J < (*I).getNumOperands(); ++J){
                    if((*I).getOperand(J)->hasName()){
                        Variable var = Variable((*I).getOperand(J));
                        if(domain->Contains(var) && !def->Contains(var))  use->Add(var);
                    }
                }
                if((*I).hasName()){
                    def->Add(Variable(&*I));
                }                
            }

            // Handling PHI node 
            {
                auto gNode = graph->GetNode(node);
                for(auto bb : graph->GetIn(gNode,Direction::BACKWARD)){
                    if(bb->getInstList().front().getOpcode() == Instruction::PHI){
                        for (int opr=0; opr<bb->getInstList().front().getNumOperands(); ++opr){
                            if(bb->getInstList().front().getOperand(opr)->hasName()){
                                auto phi = dyn_cast<PHINode>(&bb->getInstList().front());
                                if(node->getName().compare(phi->getIncomingBlock(opr)->getName())){
                                    in->Remove(Variable(bb->getInstList().front().getOperand(opr)));
                                }
                            }
                        }                        
                    }
                }
            }   //

            BoundedSet<Variable>* tmp = domain->EmptySet();
            in->Difference(def,tmp);
            tmp->Union(use,out);
        }
    };
}

SETUP(LA);
