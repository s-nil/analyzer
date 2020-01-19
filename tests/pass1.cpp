#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/ADT/Statistic.h"
// #include "IterableList.h"
// #include "FlowSet.h"
#include "Base.h"
#include "Derived.h"
#include <vector>

using namespace llvm;
using namespace L;
using namespace std;

namespace {
    struct pass1: public FunctionPass {
        static char ID;
        pass1(): FunctionPass(ID){};
        
        virtual bool runOnFunction(Function &F)
        {
            errs() << "function name: " << F.getName().str() << '\n';

            // A::IterableList<llvm::Value*> l;
            // if(F.arg_size() > 0)
            // {
            //     for(int i=0; i<F.arg_size(); ++i)
            //     {
            //         l.push_back(static_cast<llvm::Value*>(F.getArg(i)));
            //     }
            // }
	        // for(auto it = l.begin(); it!=l.end(); ++it)
	        // {
		    //     errs() << (*it) << " ";
	        // }

            // A::IterableList<int> ll;

            // A::FlowSet<int> aa;

            // aa.display();

            Base<int> b(4);
            errs() << b.get()<<'\n';

            Derived<int> d(5);
            errs() << d.get()<<'\n';

            return false;
        }
    };
    
}

char pass1::ID = 0;
static RegisterPass<pass1> X("pass1","pass 1");
