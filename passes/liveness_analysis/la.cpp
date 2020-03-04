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
#include "ArrayPackedSet.h"
#include "BackwardFlowAnalysis.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */

using namespace llvm;
using namespace std;
using namespace A;

namespace {
    struct LA: public FunctionPass, public BackwardFlowAnalysis<ArrayPackedSet<Variable>> {
        static char ID;
        string funcName;
        A::FlowSet<A::Variable> *domain;
 
        LA(string f): funcName(f), FunctionPass(ID){};
        
        virtual bool runOnFunction(Function &F)
        {
            if(demangle(F.getName().str()).substr(0,funcName.size()).compare(funcName) != 0)
                return false;
            errs() << "function name: " << demangle(F.getName().str()) << '\n';

            ArrayPackedSet<Variable> fs(&F);
            domain = &fs;

            SetFunction(&F);
            DoAnalysis();

            return false;
        }

        ArrayPackedSet<Variable>* NewInitialFlowSet() override{
            return dynamic_cast<ArrayPackedSet<Variable>*>(domain->EmptySet());

        }

        ArrayPackedSet<Variable>* EntryInitialFlowSet() override{
            return dynamic_cast<ArrayPackedSet<Variable>*>(domain->EmptySet());
        }

        void Merge(ArrayPackedSet<Variable>* in1, ArrayPackedSet<Variable>* in2, ArrayPackedSet<Variable>* out) override{
            in1->Union(in2,out);
        }

        void Copy(ArrayPackedSet<Variable>* in1, ArrayPackedSet<Variable>* in2) override{
            in1->Copy(in2);
        }
        
        void FlowThrough(BasicBlock* node, ArrayPackedSet<Variable>* in, ArrayPackedSet<Variable>* out) override{
            ArrayPackedSet<Variable>* def = dynamic_cast<ArrayPackedSet<Variable>*>(domain->EmptySet());
            ArrayPackedSet<Variable>* use = dynamic_cast<ArrayPackedSet<Variable>*>(domain->EmptySet());
            
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

            ArrayPackedSet<Variable>* tmp = dynamic_cast<ArrayPackedSet<Variable>*>(domain->EmptySet());
            in->Difference(def,tmp);
            tmp->Union(use,out);
        }
    };
    
}

char LA::ID = 0;

int main(int argc, char **argv){
    if(argc < 3){
        llvm::errs() << RED <<"Usage: " <<RESET
                        << YELLOW <<argv[0] << " <IR file> <function name>" << RESET<<'\n';
        exit(1);
    }

    SMDiagnostic Err;
    LLVMContext Context;
    std::unique_ptr<Module> Mod(parseIRFile(argv[1],Err,Context));

    if(!Mod){
        Err.print(argv[0],errs());
        return 1;
    }

    legacy::PassManager PM;
    PM.add(new LA(argv[2]));
    PM.run(*Mod);

    return 0;
}