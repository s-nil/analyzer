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
#include "Iterable.h"
#include "AbstractFlowSet.h"
#include "AbstractBoundedFlowSet.h"
#include "ObjectIntMapper.h"
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

            return false;
        }
    };
    
}

char pass1::ID = 0;
static RegisterPass<pass1> X("pass1","pass 1");
