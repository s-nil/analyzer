#include "ArrayPackedSet"
#include "ArraySparseSet"
#include "BackwardFlowAnalysis"
#include "ForwardFlowAnalysis"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define GREEN  "\033[32m"      /* Green */
#define BLUE  "\033[34m"      /* Blue */
#define MAGENTA  "\033[35m"      /* Magenta */
#define CYAN  "\033[36m"      /* Cyan */

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

using namespace llvm;
using namespace std;
using namespace A;


