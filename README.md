# analyzer
---
This is **analyzer**. A interactive data flow framework (intraprocedural and interprocedural) for LLVM.  
This README describes how to build the project. For the documentation you need to generate the docs by yourselves. Instructions for generating the docs are also given below.  

###  Dependencies  

The following components are required to be installed on your system already:
(versions written in the brackets are being used in development)  
- cmake (>=3.15.0)
- GNU Make (>=4.1)
- LLVM (>=9.0.0)
- clang (>=9.0.0)
- doxygen (>=1.8.16) ( to generate documents )

Install cmake, GNU Make and doxygen using APT package handling utility.
### Getting the source code the building analyser

checkout analyser:  
```shell
git clone https://github.com/s-nil/analyzer.git
cd analyzer
```
As analyzer requires llvm and clang, use ```install.sh``` to build llvm and clang:  
```shell
bash install.sh
```
This installer downloads llvm and clang source codes in the home directory of the user and builds them at the same place. After the completion of the building process add ```$HOME/llvm-9.0.0/build/bin``` in your PATH environment variable.  

Alternatively, pre-built binaries are also available for llvm and clang:
```shell
wget http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz
tar xvf clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz 
cd clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04/
mv clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04/ llvm-9.0.0/
```
Don't forget to add ```$HOME/llvm-9.0.0/build/bin``` in your PATH environment variable.  

Now, build analyzer:
```shell
mkdir build
cd build
cmake ..
make
```
The library has been built now. But to use this library you need to write a pass for a perticular data flow analysis. 

### Usage
Example is showing how to do liveness analysis. Find in passes/liveness_analysis.

- Create a class inheriting FunctionPass and BackwardFlowAnalysis or ForwardFlowAnalysis. As data member define a string for function name and pointer to FlowSet\<Variable\>;
	example:
```cpp
class LA : public FunctionPass, public BackwardFlowAnalysis<A>

	static char ID;
	string funcName;
	FlowSet<Variable> *domain;
```
where,
A is Abstratct Type.
A can be same as  : ArrayPackedSet\<Variable\>

- Create a constructor with a method name on which you want to do the analysis. Override runOnFunction() method. Create a ArrayPackedSet or ArraySparseSet with function and after that call DoAnalysis().
	example:
```cpp
LA(string f): funcName(f),FunctionPass(ID){};

runOnFunction(Function &F){
    ArrayPackedSet<Variable> fs(&F);
    domain = &fs;
    DoAnalysis();
}
```
- Override ```EntryInitialFlowSet()``` and ```NewInitialFlowSet()``` and return the appropriate object.
	example:
```cpp
ArrayPackedSet<Variable>* EntryInitialFlowSet() override{
    return dynamic_cast<ArrayPackedSet<Variable>*>(domain->EmptySet());
}

ArrayPackedSet<Variable>* NewInitialFlowSet() override{
    return dynamic_cast<ArrayPackedSet<Variable>*>(domain->EmptySet());
}

```
- Override ```Merge()```,```Copy()``` and ```FlowThrough()```.
	example:
```cpp
void Merge(ArrayPackedSet<Variable>* in1, ArrayPackedSet<Variable>* in2, ArrayPackedSet<Variable>* out) override{
    in1->Union(in2,out);
}

void Copy(ArrayPackedSet<Variable>* in1, ArrayPackedSet<Variable>* in2) override{
    in1->Copy(in2);
}

void FlowThrough(BasicBlock* node, ArrayPackedSet<Variable>* in, ArrayPackedSet<Variable>* out){	
    // define kill
    // define gen

    ArrayPackedSet<Variable>* tmp = dynamic_cast<ArrayPackedSet<Variable>*>(domain->EmptySet());
    in->Difference(kill,tmp);
    tmp->Union(gen,out);
}
```