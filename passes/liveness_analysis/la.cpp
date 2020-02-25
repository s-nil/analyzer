/**
 * @file pass1.cpp
 * @author Sunil Singh (sunilp896@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-01-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "llvm/Pass.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/BitVector.h"
#include "AbstractFlowSet.h"
#include "AbstractBoundedFlowSet.h"
#include "ObjectIntMapper.h"
#include "ArraySparseSet.h"
#include "ArrayPackedSet.h"
#include "ForwardFlowAnalysis.h"
#include "BackwardFlowAnalysis.h"
#include <vector>

using namespace llvm;
using namespace std;
using namespace A;

namespace {
    struct LA: public FunctionPass, public A::ForwardFlowAnalysis<A::ArrayPackedSet<char*>> {
        static char ID;
        LA(): FunctionPass(ID){};
        
        virtual bool runOnFunction(Function &F)
        {
            errs() << "function name: " << F.getName().str() << '\n';

            A::ObjectIntMapper<int> oim;
            errs() << oim.Size()<<'\n';
            oim.Add(21);
            oim.Add(213);
            oim.Add(521);
            errs() << oim.Size()<<'\n';

            // A::ArrayPackedSet<int> aps(oim);
            // errs() << aps.Size() << '\n';
            // errs() << aps.IsEmpty() << '\n';

            // A::ArrayPackedSet<int> aps1(oim);
            // errs() << aps1.Size() << '\n';
            // errs() << aps1.IsEmpty() << '\n';

            // aps.Copy(&aps1);
            // errs() << aps1.Size() << '\n';
            // errs() << aps1.IsEmpty() << '\n';

            // auto ls = aps.ToList();
            // llvm::errs() << ls.size()<<'\n';
            // for (auto i = ls.begin(); i != ls.end(); ++i)
            // {
            //     llvm::errs() << *i <<'\n';
            // }

            // llvm::BitVector bits(10);
            // bits.set(0);
            // bits.set(5);
            
            // errs() << bits.empty() <<'\n';
            // errs() << bits.count() <<'\n';
                

            SetFunction(&F);
            DoAnalysis();

            return false;
        }

        A::ArrayPackedSet<char*> NewInitialFlowSet() override{

        }

        A::ArrayPackedSet<char*> EntryInitialFlowSet() override{

        }

        void Merge(A::ArrayPackedSet<char*> in1, A::ArrayPackedSet<char*> in2, A::ArrayPackedSet<char*> out) override{

        }

        void Copy(A::ArrayPackedSet<char*> in1, A::ArrayPackedSet<char*> in2) override{

        }

    };
    
}

char LA::ID = 0;

int main(int argc, char **argv){
    SMDiagnostic Err;
    LLVMContext Context;
    std::unique_ptr<Module> Mod(parseIRFile(argv[1],Err,Context));

    if(!Mod){
        Err.print(argv[0],errs());
        return 1;
    }

    legacy::PassManager PM;
    PM.add(new LA());
    PM.run(*Mod);

    return 0;
}