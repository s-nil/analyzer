#include "ArrayPackedSet"
#include "ArraySparseSet"
#include "BackwardFlowAnalysis"
#include "ForwardFlowAnalysis"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define GREEN  	"\033[32m"      /* Green */
#define BLUE  	"\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN  	"\033[36m"      /* Cyan */

#define REGISTER_PASS(m_pass_name)  \
        legacy::PassManager PM; \
        PM.add(new m_pass_name(argv[2]));   \
        PM.run(*Mod);

#define PARSE_FILE \
        SMDiagnostic Err;   \
        LLVMContext Context;    \
        std::unique_ptr<Module> Mod(parseIRFile(argv[1],Err,Context));  \
        if(!Mod){   \
            Err.print(argv[0],errs());  \
            return 1;   \
        }

#define CHECK_ARG \
        if(argc < 3){ \
            llvm::errs() << RED <<"Usage: " <<RESET \
                        << YELLOW <<argv[0] << " <IR file> <function name>" << RESET<<'\n'; \
            exit(1);    \
        }

#define MAIN_F(m_pass_name) \
        int main(int argc, char **argv){ \
            CHECK_ARG  \
            PARSE_FILE  \
            REGISTER_PASS(m_pass_name)   \
            return 0;   \
        }


#define SETUP(m_pass_name) \
        char m_pass_name::ID = 0; \
        MAIN_F(m_pass_name)

#define BACKWARDANALYSIS(m_pass_name,m_storetype,m_property)    \
        struct m_pass_name: public FunctionPass, public BackwardFlowAnalysis<m_storetype<m_property>>

#define FORWARDANALYSIS(m_pass_name,m_storetype,m_property)    \
        struct m_pass_name: public FunctionPass, public ForwardFlowAnalysis<m_storetype<m_property>>

#define AP_INITIALVALUE()       \
        ArrayPackedSet<Variable>* NewInitialFlowSet() override

#define AP_ENTRYVALUE()       \
        ArrayPackedSet<Variable>* EntryInitialFlowSet() override

#define AP_MERGE(m_property)      \
        void Merge(ArrayPackedSet<m_property>* in1, ArrayPackedSet<m_property>* in2, ArrayPackedSet<m_property>* out) override

#define AP_COPY(m_property)       \
        void Copy(ArrayPackedSet<m_property>* in1, ArrayPackedSet<m_property>* in2) override

#define AP_FLOWTH(m_property)   \
        void FlowThrough(llvm::BasicBlock* node, ArrayPackedSet<m_property>* in, ArrayPackedSet<m_property>* out) override

#define AS_INITIALVALUE()       \
        ArraySparseSet<Variable>* NewInitialFlowSet() override

#define AS_ENTRYVALUE()       \
        ArraySparseSet<Variable>* EntryInitialFlowSet() override

#define AS_MERGE(m_property)      \
        void Merge(ArraySparseSet<m_property>* in1, ArraySparseSet<m_property>* in2, ArraySparseSet<m_property>* out) override

#define AS_COPY(m_property)       \
        void Copy(ArraySparseSet<m_property>* in1, ArraySparseSet<m_property>* in2) override

#define AS_FLOWTH(m_property)   \
        void FlowThrough(llvm::BasicBlock* node, ArraySparseSet<m_property>* in, ArraySparseSet<m_property>* out) override

#define RUN()   \
        virtual bool runOnFunction(Function &F) override

#define EXTRACT(m_property)	\
	template<>	\
	A::ValueUniverse<m_property>::ValueUniverse(Function* f)

#define SETUP_FUNCTION()	\
	do {	\
		if(demangleName(F).substr(0,funcName.size()).compare(funcName) != 0)		\
    		return false;	\
		SetFunction(&F);	\
	}while(0)


using namespace llvm;
using namespace std;
using namespace A;

string demangleName(Function& F){
	return demangle(F.getName().str());
}
