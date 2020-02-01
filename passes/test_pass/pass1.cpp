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
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/ADT/Statistic.h"
#include "AbstractFlowSet.h"
#include "AbstractBoundedFlowSet.h"
#include "ObjectIntMapper.h"
#include "ArrayPackedSet.h"
#include "llvm/ADT/BitVector.h"
#include <vector>

using namespace llvm;
using namespace std;

namespace {
    struct pass1: public FunctionPass {
        static char ID;
        pass1(): FunctionPass(ID){};
        
        virtual bool runOnFunction(Function &F)
        {
            errs() << "function name: " << F.getName().str() << '\n';

            A::ObjectIntMapper<int> oim;
            errs() << oim.Size()<<'\n';
            oim.Add(21);
            oim.Add(213);
            oim.Add(521);
            errs() << oim.Size()<<'\n';

            A::ArrayPackedSet<int> aps(oim);
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
                

            return false;
        }
    };
    
}

char pass1::ID = 0;
static RegisterPass<pass1> X("pass1","pass 1");
