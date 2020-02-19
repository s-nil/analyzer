#include "FlowAnalysis.h"
#include "llvm/Support/raw_ostream.h"

/**
 * @brief 
 * 
 * @tparam T 
 * @return T 
 */
template<typename T>
T A::FlowAnalysis<T>::NewInitialFlowSet(){

}

/**
 * @brief 
 * 
 * @tparam T 
 * @return T 
 */
template<typename T>
T A::FlowAnalysis<T>::EntryInitialFlowSet(){

}

/**
 * @brief 
 * 
 * @tparam T 
 * @param in1 
 * @param in2 
 * @param out 
 */
template<typename T>
void A::FlowAnalysis<T>::Merge(T in1, T in2, T out){

}

/**
 * @brief 
 * 
 * @tparam T 
 * @param in1 
 * @param in2 
 */
template<typename T>
void A::FlowAnalysis<T>::Copy(T in1, T in2){

}

/**
 * @brief 
 * 
 * @tparam T 
 * @param node 
 * @return T 
 */
template<typename T>
T A::FlowAnalysis<T>::GetFlowBefore(llvm::BasicBlock* node){

}

/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
void A::FlowAnalysis<T>::doAnalysis(){
    llvm::errs() << "hello in flowAnalysis\n";
}

template class A::FlowAnalysis<int>;
template class A::FlowAnalysis<char*>;